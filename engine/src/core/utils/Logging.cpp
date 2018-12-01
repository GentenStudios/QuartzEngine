/**
 *  @file logging.cpp
 *  @brief Function definitions for logging.hpp
 */

#include <engine/core/utils/Logging.hpp>

#include <cstdio>

#ifdef PHX_OS_WINDOWS
	#include <Windows.h>
	#undef ERROR // Windows is a dick
#endif

using namespace phx;

namespace phx { namespace os_terminal {

#ifdef PHX_OS_WINDOWS
	// WARNING: Do not change the order of this array, (it needs to match the order of `phx::Console::Color`)
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
		FOREGROUND_BLUE, // dark blue
		FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_BLUE // magenta
	};
#endif

#ifdef PHX_OS_LINUX
	// TODO: Gonna need a lookup table of ANSI color codes.
#endif
}}

void Console::setTextColor(const Console::Color& color)
{
#ifdef PHX_OS_WINDOWS
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(console, os_terminal::s_win32TerminalColors[static_cast<size_t>(color)]);
#endif

#ifdef PHX_OS_LINUX
	// TODO: You should just be able to insert the appropriate ANSI color code into stdout.
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

	LogVerbosityLookup[0] = "ERROR";
	LogVerbosityLookup[1] = "WARNING";
	LogVerbosityLookup[2] = "INFO";
	LogVerbosityLookup[3] = "DEBUG";

	std::ios::sync_with_stdio(false);

	// This has to go at the end, as logging capabilities are not actually ready until now :D
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
	case LogVerbosity::ERROR:   col = Console::Color::RED;        break;
	case LogVerbosity::WARNING: col = Console::Color::YELLOW;     break;
	case LogVerbosity::INFO:    col = Console::Color::GREEN;      break;
	case LogVerbosity::DEBUG:   col = Console::Color::DARK_GREEN; break;
	default:                    col = Console::Color::MAGENTA;    break; // shit's hit the fan - this shouldn't happen.
	}

	return col;
}

void Logger::logMessage(std::string errorFile, int lineNumber, std::string subSectors, std::string message, LogVerbosity verbosity)
{
	if (verbosity > m_vbLevel)
		return;

	Console::setTextColor(getColorFromVerbosity(verbosity));

	const char* verbosityString = LogVerbosityLookup[static_cast<size_t>(verbosity)];
	
	/*
		Log messages are in the format:
			[ERROR/INFO/DEBUG/WARNING] <file of log>: <line number> <message>
			             ^                          ^                   ^
			Verbosity of message          If verbosity != INFO    The message to log
	*/

	std::stringstream logMessageStream;
	logMessageStream << "[" << verbosityString << "] " << subSectors;
	
	if (verbosity != LogVerbosity::INFO) // Print the erroring file and line number if the message is not classed as INFO
	{
		logMessageStream << errorFile << ":" << lineNumber << " ";
	}

	logMessageStream << message;

	std::string logMessageString = logMessageStream.str();

	if (message == m_prevMessage)
	{
		m_currentDuplicates++;

		// Append the `(<number of times this message has been logged>)` to the end of the log message
		// - done by overwriting the previous message, and then rewriting it will the added `(...)` at the end.
		m_logFileHandle << '\r' << m_prevMessage << " (" << m_currentDuplicates << ")";
		std::cout       << '\r' << logMessageString << " (" << m_currentDuplicates << ")";
	}
	else 
	{
		m_currentDuplicates = 1;
		m_prevMessage       = message;

		m_logFileHandle << '\n' << logMessageString;
		std::cout       << '\n' << logMessageString;
	}

	Console::setTextColor(Console::Color::WHITE);
}
