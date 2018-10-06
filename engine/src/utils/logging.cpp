/**
 *  @file logging.cpp
 *  @brief Function definitions for logging.hpp
 */

#include "engine/common.hpp"

#include "engine/utils/logging.hpp"
#include <cstdio>
#include <ctime>

using namespace pheonix;

// Declarations to get rid of compiler errors
std::string Logger::m_logFile;
std::ofstream Logger::m_logFileHandle;
LogVerbosity Logger::m_vbLevel = LogVerbosity::INFO;


/** @details ENUM Lookup Table for the LogVerbosity enum class
 *  For example, LogVerbosity::INFO is equal to 2,
 *  as it is defined in the enum class. If that value
 *  is used as an array index, it will return the "string"
 *  version. This can then be printed, reducing the need for
 *  an unnecessary switch-case statement.
 */
const char* Logger::LogVerbosityLookup[] = {
        "ERROR",
        "WARNING",
        "INFO",
        "DEBUG"
};

void Logger::init( std::string logFile = "logs/pheonix.log", LogVerbosity verbosityLevel = LogVerbosity::INFO)
{
    // Setting the file names
    Logger::m_logFile = logFile;

    Logger::m_vbLevel = verbosityLevel;

    // Creating the files
    Logger::m_logFileHandle.open( Logger::m_logFile, std::ios::app );
}

void Logger::destroy()
{
    Logger::m_logFileHandle.close();
}

void Logger::logMessage( std::string errorFile, int lineNumber, std::string message, LogVerbosity verbosity)
{
    if (verbosity <= Logger::m_vbLevel ) // Make sure the logging call has a verbosity level below the defined level set at initialisation.
    {
        std::stringstream logMessage;
        logMessage << "[" << Logger::LogVerbosityLookup[static_cast<int>(verbosity)] << "] "; // Add the [INFO]/etc... at the beginning, via the use of a lookup table.

        // Add time stamp to line
        std::time_t t = std::time(0);   // get time now
        std::tm* now = std::localtime(&t);

        logMessage << "["
                  << (now->tm_year + 1900)  << '-'
                  << (now->tm_mon + 1)      << '-'
                  <<  now->tm_mday          << " "
                  <<  now->tm_hour          << ":"
                  <<  now->tm_min           << ":"
                  <<  now->tm_sec
                  << "] ";

        if (verbosity != LogVerbosity::INFO) // Print the erroring file and line number if the message is not classed as INFO
        {
            logMessage << errorFile << ":" << lineNumber << " ";
        }

        logMessage << message << std::endl;

        m_logFileHandle << logMessage.str();
        std::cout << logMessage.str() << std::endl;
    }
}
