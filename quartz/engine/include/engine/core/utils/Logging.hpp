/**
 *  @file Logging.hpp
 *  @brief Class and #defines for the logger.
 */

#pragma once

#include <engine/core/Core.hpp>

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#define INITLOGGER(logFile, vbLevel) 	phx::Logger::get()->init( logFile, vbLevel )
#define DESTROYLOGGER()              	phx::Logger::get()->destroy()

#ifdef PHX_OS_WINDOWS
#	define LERROR(message, ...)            phx::Logger::get()->log(phx::LogVerbosity::ERROR, __FILE__, __LINE__, "", message, __VA_ARGS__)
#	define LINFO(message, ...)             phx::Logger::get()->log(phx::LogVerbosity::INFO, __FILE__, __LINE__, "", message, __VA_ARGS__)
#	ifdef PHX_DEBUG
#		define LDEBUG(message, ...)        phx::Logger::get()->log(phx::LogVerbosity::DEBUG, __FILE__, __LINE__, "", message, __VA_ARGS__)
#		define LWARNING(message, ...)      phx::Logger::get()->log(phx::LogVerbosity::WARNING, __FILE__, __LINE__, "", message, __VA_ARGS__)
#	else
#		define LDEBUG(message, ...)
#		define LWARNING(message, ...)
#	endif
#else
#	define LERROR(message, ...)            phx::Logger::get()->log(phx::LogVerbosity::ERROR, __FILE__, __LINE__, "", message, ##__VA_ARGS__)
#	define LINFO(message, ...)             phx::Logger::get()->log(phx::LogVerbosity::INFO, __FILE__, __LINE__, "", message, ##__VA_ARGS__)
#	ifdef PHX_DEBUG
#		define LDEBUG(message, ...)        phx::Logger::get()->log(phx::LogVerbosity::DEBUG, __FILE__, __LINE__, "", message, ##__VA_ARGS__)
#		define LWARNING(message, ...)      phx::Logger::get()->log(phx::LogVerbosity::WARNING, __FILE__, __LINE__, "", message, ##__VA_ARGS__)
#	else
#		define LDEBUG(message, ...)
#		define LWARNING(message, ...)
#	endif
#endif

namespace phx
{
	class Console
	{
	public:
		/**
		 * @brief The fixed list colors that text can be set to in the console. 
		 */
		enum class Color
		{
			RED         = 0,
			GREEN       = 1,
			BLUE        = 2,
			YELLOW      = 3,
			WHITE       = 4,
			BLACK       = 5,
			DARK_YELLOW = 6,
			DARK_RED    = 7,
			DARK_GREEN  = 8,
			DARK_BLUE   = 9,
			MAGENTA     = 10
		};

		/**
		 * @brief Set the text color for any preceding text (stdout). The color will remain as set here until it is changed by another `setTextColor` call.
		 * @param color The color to set any preceding text to.
		 */
		static void setTextColor(const Color& color);
	private:
	};

	/**
	 * @brief This is what will define whether certain messages are low enough a verbosity to be outputted.
	 */
	enum class LogVerbosity
	{
		ERROR	= 0, ///< ERROR Is for critical messages that result in FAILURES
		WARNING = 1, ///< WARNING More verbose logging, for errors that are not FATAL, but are errors none-the-less
		INFO	= 2, ///< INFO For important information which can aid finding problems quickly
		DEBUG	= 3, ///< DEBUG For absolutely everything, like entering a function to exiting the function.
	};

	/**
	 * @brief Class for Logging. Literally.
	 * 
	 */
	class Logger
	{
	private:
		template <typename T, typename... Args>
		void log(std::stringstream& sstream, const T& msg, const Args&... args) {
			sstream << msg;
			log(sstream, args...);
		}

		void log(std::stringstream& sstream) {}

	public:
		/**
		 * @brief Fetches the static instance of the Logger (yes it's a singleton...)
		 * @return A pointer to the static instance of the logger. Don't try to `delete` or `free` this pointer, please.
		 */
		static Logger* get();

		/**
		 * @brief Initialise the Logger, open file and set the initial logging verbosity level.
		 * @param logFile The file in which log messages should be outputted to, as well as the console.
		 * @param verbosityLevel The initial logging verbosity, dictates what should and shouldn't be outputted, by referring to LogVerbosity.
		 */
		void init(const std::string& logFile, LogVerbosity verbosityLevel);

		/**
		 * @brief Destroy the logger, by closing the log file.
		 */
		void destroy();

		/**
		 * @brief Processes the string and the concatenates the varadics args.
		 * @param verbosity     The verbosity of the message, dictates whether the message is outputted or not.
		 * @param errorFile     The file from which the error is occurring
		 * @param lineNumber    The line from which the error is occurring
		 * @param subSectors	Extra [sections] that a message may need for better specialization.
		 * @param message       The actual message to be logged.
		 * @param args			A series of 0 or more different types to be added to the end of `message`
		 */
		template <typename... Args>
		void log(LogVerbosity verbosity, const std::string& errorFile, int lineNumber, const std::string& subSectors, const std::string& message, const Args&... args)
		{
			std::stringstream ss;
			ss << message;
			log(ss, args...);
			logMessage(errorFile, lineNumber, subSectors, ss.str(), verbosity);
		}


	private:
		/**
		 * @brief logMessage is to actually log the message to the console and the file opened by init();
		 * @param errorFile     The file from which the error is occurring
		 * @param lineNumber    The line from which the error is occurring
		 * @param message       The actual message to be logged.
		 * @param verbosity     The verbosity of the message, dictates whether the message is outputted or not.
		 */
		void logMessage(std::string errorFile, int lineNumber, std::string subSectors, std::string message, LogVerbosity verbosity);

		Logger() {};
		~Logger() {}

		/// @brief String for the file to log to.
		std::string m_logFile;

		/// @brief The file handle for the logging file, opened by init(), and closed by destroy().
		std::ofstream m_logFileHandle;

		/// @brief The initial logging level that is referred to, to dictate what gets logged and what doesn't.
		LogVerbosity m_vbLevel;

		/// @brief The lookup table for ENUM, so something can get outputted like "[ERROR]"
		const char* LogVerbosityLookup[4];

		/// @brief The previous message that has been logged.
		std::string m_prevMessage;

		/// @brief The number of times the current message has tried to be logged
		size_t m_currentDuplicates;
	};

}
