// Copyright 2019 Genten Studios
// 
// Redistribution and use in source and binary forms, with or without modification, are permitted provided that the 
// following conditions are met:
// 
// 1. Redistributions of source code must retain the above copyright notice, this list of conditions and the 
// following disclaimer.
// 
// 2. Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the 
// following disclaimer in the documentation and/or other materials provided with the distribution.
// 
// 3. Neither the name of the copyright holder nor the names of its contributors may be used to endorse or promote 
// products derived from this software without specific prior written permission.
// 
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED 
// WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A 
// PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY 
// DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, 
// PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER 
// CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR 
// OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH 
// DAMAGE.

#include <Quartz/Core/QuartzPCH.hpp>
#include <Quartz/Core/Utilities/Logger.hpp>

#include <iostream>

#if defined(QZ_PLATFORM_WINDOWS)
#include <Windows.h>
#endif

static const char* g_logVerbosityTable[] = {
		"ERROR",
		"WARNING",
		"INFO",
		"DEBUG"
};

#if defined(QZ_PLATFORM_WINDOWS)
static WORD s_windowsTermCol[] =
{
	FOREGROUND_INTENSITY | FOREGROUND_RED,										// Red
	FOREGROUND_INTENSITY | FOREGROUND_BLUE,										// Blue
	FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN,					// Yellow
	FOREGROUND_INTENSITY | FOREGROUND_GREEN,									// Green
	FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE, // White
};
#endif

#if defined(QZ_PLATFORM_LINUX)
static const char* s_linuxTermCol[] =
{
	"\033[1;31m", // Red
	"\033[1;34m", // Blue
	"\033[0;33m", // Yellow
	"\033[1;32m", // Green
	"\033[1;37m"  // White
};
#endif

using namespace qz::utils;
using namespace qz;

Logger::LogMessage::LogMessage(LogVerbosity verbosity, const std::string& errorFileName, int errorFileNumber,
					   const std::string& errorMessage):
	vbLevel(verbosity), errorFile(errorFileName), lineNumber(errorFileNumber), message(errorMessage)
{
}

Logger* Logger::instance()
{
	static Logger logger;
	return &logger;
}

void Logger::initialize(const std::string& filePath, const LogVerbosity verbLevel, LogConfigurations flags)
{
	m_verbosity = verbLevel;

	if (hasFlag(flags, LogConfigurations::LOG_TO_FILE))
		m_fileHandle.open(filePath, std::ios::out | std::ios::app);

	if (hasFlag(flags, LogConfigurations::USE_COLORS))
		m_useColors = true;
	
	if (hasFlag(flags, LogConfigurations::USE_THREADS))
		m_useThreads = true;

	if (m_useThreads)
	{
		m_worker = std::unique_ptr<threading::CustomWorker<LogMessage>>();

		// This is some painful C++, the Logger::* is a member pointer thingy. The static_cast is to help C++ determine which overload of logMessage
		// that std::bind should use.
		m_worker->setFunction(std::bind(static_cast<void(Logger::*)(const LogMessage&)>(&Logger::logMessage), this, std::placeholders::_1));
	}
}

void Logger::destroy()
{
	if (m_useThreads)
		m_worker->cleanExit();
	
	m_useColors = false;
	m_useThreads = false;
	m_verbosity = LogVerbosity::INFO;
	m_currentDuplicates = 0;
	m_worker.reset(); // resetting the smart ptr. (there's no reset function on the actual worker) :)
	m_fileHandle.close();
}

Logger::Logger() {}
Logger::~Logger() { destroy(); }

void Logger::logMessage(LogVerbosity verbosity, const std::string& errorFile, int lineNumber, const std::string& message)
{
	/*
		Log messages are in the format:
			[ERROR/INFO/DEBUG/WARNING] <file of log>: <line number> <message>
						 ^             ^^^^^^^^^^^^^^^^^^^^^^^^^^^^     ^
		  Message importance/verbosity   If verbosity != INFO    The actual message
	*/

	if (m_useColors)
	{
		QZ_IF_WINDOWS(SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), s_windowsTermCol[static_cast<std::size_t>(verbosity)]));
		QZ_IF_LINUX(std::cout << s_linuxTermCol[static_cast<std::size_t>(verbosity)]);
	}

	const std::string verbosityString = g_logVerbosityTable[static_cast<size_t>(verbosity)];

	char* finalMessage = nullptr;

	// Calculates the size of the buffer, dependent on the layout of the log output.
	// The general layout is "[%s] %s:%d %s". The +6 at the end is the extra 5 characters in the format string (3 for the info one), and an extra one for a null terminator
	if (verbosity == LogVerbosity::INFO)
	{
		const std::size_t bufferSize = verbosityString.length() + message.length() + 4;
		finalMessage = new char[bufferSize];
		snprintf(finalMessage, bufferSize, "[%s] %s", verbosityString.c_str(), message.c_str());
	}
	else
	{
		const std::size_t bufferSize = verbosityString.length() + errorFile.length() + std::to_string(lineNumber).length() + message.length() + 6;
		finalMessage = new char[bufferSize];
		snprintf(finalMessage, bufferSize, "[%s] %s:%d %s", verbosityString.c_str(), errorFile.c_str(), lineNumber, message.c_str());
	}

	if (finalMessage == m_prevMessage)
	{
		m_currentDuplicates++;

		// The "\r" prefix makes sure that if the current message is the same as before, it will use the capabilities of a "carriage return"
		// to not waste space and "edit" the line so it doesn't spam the console like heck. We aren't printing the \r lines to a file because
		// they don't work and it will just exponentially grow the log file size.
		printf("\r %s (%zu)", finalMessage, m_currentDuplicates);
	}
	else
	{
		m_currentDuplicates = 1;
		m_prevMessage = finalMessage;

		m_fileHandle << '\n' << finalMessage;
		printf("\n %s ", finalMessage);
	}

	delete[] finalMessage;

	if (m_useColors)
	{
		QZ_IF_WINDOWS(SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), s_windowsTermCol[static_cast<std::size_t>(LogVerbosity::NONE)]););
		QZ_IF_LINUX(std::cout << s_linuxTermCol[static_cast<std::size_t>(LogVerbosity::NONE)];)
	}
}

void Logger::logMessage(const LogMessage& message)
{
	logMessage(message.vbLevel, message.errorFile, message.lineNumber, message.message);
}
