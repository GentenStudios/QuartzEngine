//
// Created by austin on 10/5/18.
//

#pragma once

#include <iostream>
#include <fstream>

namespace phoenix
{
    /* ENUM CLASS for the Logging Verbosity
     * This is what will define whether certain messages are outputted or not.
     *
     * ERROR -> Is for critical messages that result in FAILURES"
     * WARNING-> More verbose logging, for errors that are not FATAL, but are errors none-the-less
     * INFO -> For important information which can aid finding problems quickly
     * DEBUG-> For absolutely everything, like entering a function to exiting the function.
     */
    enum class LogVerbosity
    {
        ERROR = 0,
        WARNING = 1,
        INFO = 2,
        DEBUG= 3,
    };

    class Logger
    {
    public:
        Logger() {}
        ~Logger() {}

        // Initialization of logging object
        static void init( std::string logFile, LogVerbosity vbLevel );

        // Destroy the logging object
        static void destroy();

        // Output the message, while keeping in mind the verbosity level
        static void logMessage( std::string errorFile, int lineNumber, std::string message, LogVerbosity verbosity);


    private:
        static std::string m_logFile;
        static std::ofstream m_logFileHandle;
        static LogVerbosity m_vbLevel;

        // The lookup table for ENUM
        static const char* LogVerbosityLookup[];
    };

} // namespace pheonix