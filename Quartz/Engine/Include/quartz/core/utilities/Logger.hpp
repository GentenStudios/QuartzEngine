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

#pragma once

#include <quartz/core/Core.hpp>

#include <string>
#include <sstream>
#include <fstream>

#define LOGGER_INIT(x, y) qz::utils::Logger::instance()->initialise(x, y);
#define LOGGER_DESTROY() qz::utils::Logger::instance()->destroy();

#ifdef QZ_PLATFORM_WINDOWS
#	define LFATAL(message, ...)            qz::utils::Logger::instance()->log(qz::utils::LogVerbosity::FATAL, __FILE__, __LINE__, "", message, __VA_ARGS__)
#	define LINFO(message, ...)             qz::utils::Logger::instance()->log(qz::utils::LogVerbosity::INFO, __FILE__, __LINE__, "", message, __VA_ARGS__)
#	ifdef QZ_DEBUG
#		define LDEBUG(message, ...)        qz::utils::Logger::instance()->log(qz::utils::LogVerbosity::DEBUG, __FILE__, __LINE__, "", message, __VA_ARGS__)
#		define LWARNING(message, ...)      qz::utils::Logger::instance()->log(qz::utils::LogVerbosity::WARNING, __FILE__, __LINE__, "", message, __VA_ARGS__)
#	else
#		define LDEBUG(message, ...)
#		define LWARNING(message, ...)
#	endif
#else
#	define LFATAL(message, ...)            qz::utils::Logger::instance()->log(qz::utils::LogVerbosity::FATAL, __FILE__, __LINE__, "", message, ##__VA_ARGS__)
#	define LINFO(message, ...)             qz::utils::Logger::instance()->log(qz::utils::LogVerbosity::INFO, __FILE__, __LINE__, "", message, ##__VA_ARGS__)
#	ifdef QZ_DEBUG
#		define LDEBUG(message, ...)        qz::utils::Logger::instance()->log(qz::utils::LogVerbosity::DEBUG, __FILE__, __LINE__, "", message, ##__VA_ARGS__)
#		define LWARNING(message, ...)      qz::utils::Logger::instance()->log(qz::utils::LogVerbosity::WARNING, __FILE__, __LINE__, "", message, ##__VA_ARGS__)
#	else
#		define LDEBUG(message, ...)
#		define LWARNING(message, ...)
#	endif
#endif

namespace qz
{
	namespace utils
	{
		/**
		 * @brief The fixed list colors that text can be set to in the console.
		 */
		enum class TextColor : int
		{
			RED = 0,
			GREEN = 1,
			BLUE = 2,
			YELLOW = 3,
			WHITE = 4,
		};

		/**
		 * @brief This is what will define whether certain messages are low enough a verbosity to be outputted.
		 */
		enum class LogVerbosity : int
		{
			FATAL = 0,
			WARNING = 1,
			INFO = 2,
			DEBUG = 3,
		};

		/**
		 * @brief The Logger for the engine, and probably clients.
		 */
		class QZ_API Logger
		{
		public:
			/**
			 * @brief Returns the singleton instance of the logger.
			 * @return A pointer to the logger object.
			 */
			static Logger* instance();

			/**
			 * @brief Initializes the logger.
			 * @param logFile The file that should be logged to
			 * @param verbLevel The level of verbosity that should be logged.
			 */
			void initialise(const std::string& logFile, LogVerbosity verbLevel);
			
			/**
			* @brief Destroys the logger.
			* 
			* Closes the file handle, and puts an extra newline character so the next
			* terminal prompt doesn't extend on the last logged line.
			*/
			void destroy();

			/**
			 * @brief Logs the actual message.
			 * @tparam Args This allows the function to be variadic
			 * @param verbosity The verbosity of the message being logged.
			 * @param errorFile The file that the message is coming from.
			 * @param lineNumber The line in the file that the message is coming from.
			 * @param subSectors Extra narrowing down sectors for error messages.
			 * @param message The message itself.
			 * @param args The rest of the arguments to be parsed and logged.
			 */
			template <typename... Args>
			void log(LogVerbosity verbosity, const std::string& errorFile, int lineNumber, const std::string& subSectors, const std::string& message, const Args&... args)
			{
				std::stringstream ss;
				ss << message;
				log(ss, args...);
				logMessage(errorFile, lineNumber, verbosity, subSectors, ss.str());
			}

		private:
			Logger() = default;

			/// @brief The log file.
			std::string m_logFile = "quartz.log";

			/// @brief The handle to the actual log file, once it's opened.
			std::ofstream m_logFileHandle;

			/// @brief The verbosity level that the initialise function sets up.
			LogVerbosity m_vbLevel = LogVerbosity::INFO;

			std::string m_prevMessage;
			std::size_t m_currentDuplicates;

		private:
			template <typename T, typename... Args>
			void log(std::stringstream& sstream, const T& msg, const Args&... args) {
				sstream << msg;
				log(sstream, args...);
			}

			void log(std::stringstream& sstream) {}

			void logMessage(const std::string& errorFile, int lineNumber, LogVerbosity verbosity, const std::string& subSectors, const std::string& message);
		};
	}
}

