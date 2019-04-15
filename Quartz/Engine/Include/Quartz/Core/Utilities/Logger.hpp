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

#include <Quartz/Core/Core.hpp>
#include <Quartz/Core/Utilities/Threading/CustomWorker.hpp>
#include <Quartz/Core/Utilities/EnumTools.hpp>

#include <string>
#include <sstream>
#include <fstream>

#define LFATAL(message, ...)            qz::utils::Logger::instance()->log(qz::utils::LogVerbosity::FATAL, __FILE__, __LINE__, "", message, ##__VA_ARGS__)
#define LINFO(message, ...)             qz::utils::Logger::instance()->log(qz::utils::LogVerbosity::INFO, __FILE__, __LINE__, "", message, ##__VA_ARGS__)
#ifdef QZ_DEBUG
#	define LDEBUG(message, ...)        qz::utils::Logger::instance()->log(qz::utils::LogVerbosity::DEBUG, __FILE__, __LINE__, "", message, ##__VA_ARGS__)
#	define LWARNING(message, ...)      qz::utils::Logger::instance()->log(qz::utils::LogVerbosity::WARNING, __FILE__, __LINE__, "", message, ##__VA_ARGS__)
#else
#	define LDEBUG(message, ...)
#	define LWARNING(message, ...)
#endif

namespace qz
{
	namespace utils
	{
		/**
		 * @brief Enumerators for setting the verbosity of log messages.
		 */
		enum class LogVerbosity : uint
		{
			FATAL = 0,	 //< An error that is basically unrecoverable, the engine should most likely be at a state of quitting/crashing at this point.
			WARNING = 1, //< Something that is not right, but still recoverable, or non-critical - allowing a game to work like normal.
			INFO = 2,	 //< Something which is just information, like OpenGL details, or quitting/starting messages.
			DEBUG = 3,	 //< Messages useful when debugging an issue, or allowing a developer to have more verbose insights into what's happening.
			NONE = 4     //< Something which is just not important. (I (beeperdeeper) can't remember why i put it here, but ima keep it in case i ever do.)
		};

		/**
		 * @brief Configurations for the logger to adapt it's functionality towards.
		 */
		enum class LogConfigurations : uint
		{
			LOG_TO_FILE = 1 << 0,
			USE_COLORS = 1 << 1,
			USE_THREADS = 1 << 2,
		};

		/**
		 * @brief A fast, multi-threaded Logger, which logs to both file and stdout (console).
		 */
		class Logger
		{
		public:
			/**
			 * @brief Returns a pointer to the singleton object of the logger.
			 * @return The singleton object of the class.
			 */
			static Logger* instance();

			/**
			 * @brief Initializes the logger for use. (It is useable even without initialization.)
			 * @param filePath The file for the logger to log to.
			 * @param verbLevel The level of verbosity to log.
			 * @param flags Flags using LogConfigurations to configure certain options.
			 */
			void initialize(const std::string& filePath, LogVerbosity verbLevel, LogConfigurations flags);

			/**
			 * @brief Destroys the current instance of the logger, can be re-initialized whenever wanted.
			 */
			void destroy();

			/**
			 * @brief Logs a message with as many arguments a person needs. Does NOT work like a format string, but a continuous flow.
			 * @tparam Args Variadic template for basically "unlimited" arguments to log.
			 * @param verbosity The verbosity of the message.
			 * @param errorFile The file from which the message is being logged.
			 * @param lineNumber The line in the file from which the message is being logged.
			 * @param message The message itself.
			 * @param args The other remaining arguments to log.
			 */
			template <typename... Args>
			void log(LogVerbosity verbosity, const std::string& errorFile, int lineNumber, const std::string& message, const Args&... args)
			{
				if (verbosity > m_verbosity)
					return;

				std::stringstream ss;
				ss << message;
				log(ss, args...);

				if (m_useThreads)
					m_worker->enqueueData({ verbosity, errorFile, lineNumber, ss.str() });
				else
					logMessage(verbosity, errorFile, lineNumber, ss.str());
			}

		private:
			/// @brief Tells the logger whether to use colors or not.
			bool m_useColors = false;

			/// @brief Tells the logger whether to use threads or not.
			bool m_useThreads = false;

			/// @brief Tells the logger upto what verbosity it should be logging.
			LogVerbosity m_verbosity = LogVerbosity::INFO;

			/// @brief This is the last message logged.
			std::string m_prevMessage;

			/// @brief This is the amount of duplicate messages being logged, mainly so they aren't logged again and that line is updated.
			std::size_t m_currentDuplicates = 0;

			/// @brief This is the file handle used when outputting into the file.
			std::ofstream m_fileHandle;

			/**
			 * @brief Allows messages to be stored in a queue before they are logged.
			 */
			struct LogMessage
			{
				LogMessage() = default;
				LogMessage(LogVerbosity verbosity, const std::string& errorFileName, int errorFileNumber,
					const std::string& errorMessage);

				LogVerbosity vbLevel = LogVerbosity::INFO;
				std::string errorFile;
				int lineNumber = 0;
				std::string message;
			};

			/**
			 * @brief The thread worker that will be used if threading is enabled.
			 */
			std::unique_ptr<threading::CustomWorker<LogMessage>> m_worker;

		private:
			/**
			 * @brief Private constructor to allow for only a singleton.
			 */
			Logger();

			/**
			 * @brief Private destructor because... well use your brain.
			 */
			~Logger();

			/**
			 * @brief Resursively adds all the parameters into the provided stream.
			 * @tparam T The type being pushed into the stream at this point.
			 * @tparam Args The rest of the arguments being logged.
			 * @param sstream The stream being pushed into.
			 * @param msg The current message being pushed into the stream.
			 * @param args The rest of the args being logged.
			 */
			template <typename T, typename... Args>
			void log(std::stringstream& sstream, const T& msg, const Args&... args) {
				sstream << msg;
				log(sstream, args...);
			}

			/**
			 * @brief Just returns when there are no arguments and just the stream left now.
			 * @param sstream The completed stream.
			 */
			void log(std::stringstream& sstream) {}

			/**
			 * @brief Actually logs the message, the final step of the process.
			 * @param verbosity The verbosity of the message being logged.
			 * @param errorFile The file from which the message originates.
			 * @param lineNumber The line in the file from which the message was dispatched.
			 * @param message The actual message itself.
			 */
			void logMessage(LogVerbosity verbosity, const std::string& errorFile, int lineNumber, const std::string& message);

			/**
			 * @brief Facilitating function to pass each LogMessage member individually to the above logMessage function.
			 * @param message The data needing to be logged.
			 */
			void logMessage(const LogMessage& message);
		};
	}
}

ENABLE_BITMASK_OPERATORS(qz::utils::LogConfigurations);
