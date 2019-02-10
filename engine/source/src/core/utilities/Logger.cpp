#include <quartz/core/quartz-pch.hpp>
#include <quartz/core/utilities/Logger.hpp>
#include <quartz/core/Core.hpp>
#include <iostream>

#ifdef QZ_PLATFORM_WINDOWS
#	include <Windows.h>
#endif

using namespace qz::utils;

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
	std::cout << os_terminal::s_linuxTerminalColors[static_cast<std::size_t>(color)];
#endif
}

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

		m_logFileHandle << '\n' << logMessageString;
		std::cout << '\n' << logMessageString;
	}

	setTerminalTextColor(TextColor::WHITE);
}
