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
#	define LFATAL(message, ...)            qz::utils::Logger::instance()->log(qz::utils::LogVerbosity::ERROR, __FILE__, __LINE__, "", message, ##__VA_ARGS__)
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
		enum class TextColor : int
		{
			RED = 0,
			GREEN = 1,
			BLUE = 2,
			YELLOW = 3,
			WHITE = 4,
		};

		enum class LogVerbosity : int
		{
			FATAL = 0,
			WARNING = 1,
			INFO = 2,
			DEBUG = 3,
		};

		class QZ_API Logger
		{
		public:
			static Logger* instance();

			void initialise(const std::string& logFile, LogVerbosity verbLevel);
			void destroy();

			template <typename... Args>
			void log(LogVerbosity verbosity, const std::string& errorFile, int lineNumber, const std::string& subSectors, const std::string& message, const Args&... args)
			{
				std::stringstream ss;
				ss << message;
				log(ss, args...);
				logMessage(errorFile, lineNumber, verbosity, subSectors, ss.str());
			}

		private:
			Logger(): m_currentDuplicates(0) {}
			~Logger() {}

			template <typename T, typename... Args>
			void log(std::stringstream& sstream, const T& msg, const Args&... args) {
				sstream << msg;
				log(sstream, args...);
			}

			void log(std::stringstream& sstream) {}

			void logMessage(const std::string& errorFile, int lineNumber, LogVerbosity verbosity, const std::string& subSectors, const std::string& message);

			std::string m_logFile = "quartz.log";
			std::ofstream m_logFileHandle;

			LogVerbosity m_vbLevel = LogVerbosity::INFO;

			std::string m_prevMessage;
			std::size_t m_currentDuplicates;
		};
	}
}
