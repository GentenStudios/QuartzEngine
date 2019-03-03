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

#include <quartz/core/QuartzPCH.hpp>
#include <quartz/core/utilities/Logger.hpp>
#include <quartz/core/Core.hpp>
#include <iostream>

#ifdef QZ_PLATFORM_WINDOWS
#	include <Windows.h>
#endif

using namespace qz::utils;

/**
 * @brief The lookup table for converting the verbosity enums to text.
 */
static const char* g_logVerbToText[] = {
		"FATAL ERROR",
		"WARNING",
		"INFO",
		"DEBUG"
};

#ifdef QZ_PLATFORM_WINDOWS
static WORD s_windowsTermCol[] =
{
	FOREGROUND_INTENSITY | FOREGROUND_RED,										// Red
	FOREGROUND_INTENSITY | FOREGROUND_GREEN,									// Green
	FOREGROUND_INTENSITY | FOREGROUND_BLUE,										// Blue
	FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN,					// Yellow
	FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE, // White
};
#endif

#ifdef QZ_PLATFORM_LINUX
static const char* s_linuxTermCol[] =
{
	"\033[1;31m", // Red
	"\033[1;32m", // Green
	"\033[1;34m", // Blue
	"\033[0;33m", // Yellow
	"\033[1;37m"  // White
};
#endif

static void setTerminalTextColor(TextColor color)
{
#ifdef QZ_PLATFORM_WINDOWS
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(console, s_windowsTermCol[static_cast<std::size_t>(color)]);
#endif

#ifdef QZ_PLATFORM_LINUX
	std::cout << s_linuxTermCol[static_cast<std::size_t>(color)];
#endif
}

/**
 * @brief Sets the color of the terminal using the verbosity provided
 * @param vb The verbosity corresponding the color wanted.
 */
static void setTerminalTextColor(LogVerbosity vb)
{
	TextColor color;

	switch (vb)
	{
	case LogVerbosity::FATAL:   color = TextColor::RED;		break;
	case LogVerbosity::WARNING: color = TextColor::YELLOW;	break;
	case LogVerbosity::INFO:    color = TextColor::WHITE;	break;
	case LogVerbosity::DEBUG:   color = TextColor::GREEN;	break;
	default:                    color = TextColor::WHITE;	break;
	}

	setTerminalTextColor(color);
}

Logger* Logger::instance()
{
	static Logger logger;
	return &logger;
}

void Logger::initialise(const std::string& logFile, LogVerbosity verbLevel)
{
	m_logFile = logFile;
	m_vbLevel = verbLevel;

	m_logFileHandle.open(Logger::m_logFile, std::ios::out | std::ios::app);
}

void Logger::destroy()
{
	m_logFileHandle.close();
}

void Logger::logMessage(const std::string& errorFile, int lineNumber, LogVerbosity verbosity, const std::string& subSectors, const std::string& message)
{
	if (verbosity > m_vbLevel)
		return;

	setTerminalTextColor(verbosity);

	const char* verbosityString = g_logVerbToText[static_cast<size_t>(verbosity)];

	/*
		Log messages are in the format:
			[ERROR/INFO/DEBUG/WARNING] <file of log>: <line number> <message>
						 ^             ^^^^^^^^^^^^^^^^^^^^^^^^^^^^     ^
		  Message importance/verbosity   If verbosity != INFO    The actual message
	*/

	std::stringstream logMessageStream;
	logMessageStream << "[" << verbosityString << "] " << subSectors;

	// Print the erroring file and line number if the message is not just an INFO message
	if (verbosity != LogVerbosity::INFO)
	{
		logMessageStream << errorFile << ":" << lineNumber << " ";
	}

	logMessageStream << message;

	std::string logMessageString = logMessageStream.str();

	if (message == m_prevMessage)
	{
		m_currentDuplicates++;

		// The "\r" prefix makes sure that if there is a new message, but it is the same, it will rewrite that line to the console, 
		// rather than to print it out again and waste terminal space. Really useful, but may confuse people just as it did confuse me.
		m_logFileHandle << '\r' << m_prevMessage << " (" << m_currentDuplicates << ")";
		std::cout << '\r' << logMessageString << " (" << m_currentDuplicates << ")";
	}
	else
	{
		m_currentDuplicates = 1;
		m_prevMessage = message;

		m_logFileHandle << '\n' << logMessageString << '\n';
		std::cout << '\n' << logMessageString << '\n';
	}

	setTerminalTextColor(TextColor::WHITE);
}

