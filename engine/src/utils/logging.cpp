/**
 *  @file logging.cpp
 *  @brief Function definitions for logging.hpp
 */

#include "engine/common.hpp"

#ifdef PHX_OS_WINDOWS
	#include <Windows.h>
#undef ERROR
#endif

#include "engine/utils/logging.hpp"
#include <cstdio>
#include <ctime>

using namespace phx;


namespace phx { namespace os_terminal {

#ifdef PHX_OS_WINDOWS
	static WORD s_win32TerminalColors[] =
	{
		FOREGROUND_INTENSITY | FOREGROUND_RED, // red
		FOREGROUND_INTENSITY | FOREGROUND_GREEN, // green
		FOREGROUND_INTENSITY | FOREGROUND_BLUE, // blue
		FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN, // yellow
		FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE, // white
		0, // black
		FOREGROUND_RED | FOREGROUND_GREEN, // dark yellow
		FOREGROUND_RED, // dark red
		FOREGROUND_GREEN, // dark green
		FOREGROUND_BLUE // dark blue
	};
#endif

#ifdef PHX_OS_LINUX
#endif

}}

void Console::setTextColor(const Console::Color& color)
{
#ifdef PHX_OS_WINDOWS
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(console, os_terminal::s_win32TerminalColors[static_cast<size_t>(color)]);
#endif
}

void Logger::init(std::string logFile = "logs/phoenix.log", LogVerbosity verbosityLevel = LogVerbosity::INFO)
{
	// Setting the file names
	m_logFile = logFile;

	m_vbLevel = verbosityLevel;
	m_currentDuplicates = 1;
	// Creating the files
	m_logFileHandle.open(Logger::m_logFile, std::ios::app);
	
	m_lastTwoWereEqual = false;
	LogVerbosityLookup[0] = "ERROR";
	LogVerbosityLookup[1] = "WARNING";
	LogVerbosityLookup[2] = "INFO";
	LogVerbosityLookup[3] = "DEBUG";

	std::ios::sync_with_stdio(false);

	// This has to go at the end, as logging capabilitys are not actually ready until now :D
	if (!m_logFileHandle.is_open())
	{
		LERROR("Could not open log file");
	}
}

void Logger::destroy()
{
	Logger::m_logFileHandle.close();
}

Logger* Logger::get()
{
	static Logger logger;
	return &logger;
}

static Console::Color getColorFromVerbosity(LogVerbosity vb)
{
	Console::Color col;
	switch (vb)
	{
	case LogVerbosity::ERROR: col = Console::Color::RED; break;
	case LogVerbosity::WARNING: col = Console::Color::YELLOW; break;
	case LogVerbosity::INFO: col = Console::Color::GREEN; break;
	case LogVerbosity::DEBUG: col = Console::Color::DARK_GREEN; break;
	}

	return col;
}

void Logger::logMessage(std::string errorFile, int lineNumber, std::string subSectors, std::string message, LogVerbosity verbosity)
{
	if (verbosity <= Logger::m_vbLevel) // Make sure the logging call has a verbosity level below the defined level set at initialisation.
	{
		Console::setTextColor(getColorFromVerbosity(verbosity));

		std::stringstream logMessage;
		logMessage << "[" << Logger::LogVerbosityLookup[static_cast<int>(verbosity)] << "] "; // Add the [INFO]/etc... at the beginning, via the use of a lookup table.
		logMessage << subSectors;
		if (verbosity != LogVerbosity::INFO) // Print the erroring file and line number if the message is not classed as INFO
		{
			logMessage << errorFile << ":" << lineNumber << " ";
		}

		logMessage << message;

		if (logMessage.str() == m_prevMessage)
		{
			m_currentDuplicates++;
			m_logFileHandle << '\r' << m_prevMessage << " (" << m_currentDuplicates << ")";
			std::cout << '\r' << m_prevMessage << " (" << m_currentDuplicates << ")";
			m_lastTwoWereEqual = true;
			return;
		}
		else {
			m_currentDuplicates = 1;
			m_prevMessage = logMessage.str();
		}
		m_logFileHandle << '\n' << logMessage.str();
		std::cout << '\n' << logMessage.str();
	}
}
