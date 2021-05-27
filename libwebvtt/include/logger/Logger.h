///////////////////////////////////////////////////////////////////////////////
// @File Name:     Logger.h                                                  //
// @Author:        Pankaj Choudhary                                          //
// @Version:       0.0.1                                                     //
// @L.M.D:         13th April 2015                                           //
// @Description:   For Logging into file                                     //
//                                                                           //
// Detail Description:                                                       //
// Implemented complete logging mechanism, Supporting multiple logging type  //
// like as file based logging, console base logging etc. It also supported   //
// for different log type.                                                   //
//                                                                           //
// Thread Safe logging mechanism. Compatible with VC++ (Windows platform)   //
// as well as G++ (Linux platform)                                           //
//                                                                           //
// Supported Log Type: ERROR, ALARM, ALWAYS, INFO, BUFFER, TRACE, DEBUG      //
//                                                                           //
// No control for ERROR, ALRAM and ALWAYS messages. These type of messages   //
// should be always captured.                                                //
//                                                                           //
// BUFFER log type should be use while logging raw buffer or raw messages    //
//                                                                           //
// Having direct interface as well as C++ Singleton inface. can use          //
// whatever interface want.                                                   //
//                                                                           //
///////////////////////////////////////////////////////////////////////////////

#ifndef _LOGGER_H_
#define _LOGGER_H_

// C++ Header File(s)
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <memory>
#include <mutex>

#ifdef WIN32
// Win Socket Header File(s)
#include <Windows.h>
#include <process.h>
#else
// POSIX Socket Header File(s)
#include <errno.h>
#include <pthread.h>
#endif

namespace CPlusPlusLogging
{


   // enum for LOG_LEVEL
   typedef enum LOG_LEVEL
   {
      DISABLE_LOG = 1,
      LOG_LEVEL_INFO = 2,
      LOG_LEVEL_BUFFER = 3,
      LOG_LEVEL_TRACE = 4,
      LOG_LEVEL_DEBUG = 5,
      ENABLE_LOG = 6,
   } LogLevel;

   // enum for LOG_TYPE
   typedef enum LOG_TYPE
   {
      NO_LOG = 1,
      CONSOLE = 2,
      FILE_LOG = 3,
   } LogType;

   class Logger
   {
   public:
      // Interface for Error Log
      void error(const char *text) throw();
      void error(std::string &text) throw();
      void error(std::ostringstream &stream) throw();

      // Interface for Alarm Log
      void alarm(const char *text) throw();
      void alarm(std::string &text) throw();
      void alarm(std::ostringstream &stream) throw();

      // Interface for Always Log
      void always(const char *text) throw();
      void always(std::string &text) throw();
      void always(std::ostringstream &stream) throw();

      // Interface for Buffer Log
      void buffer(const char *text) throw();
      void buffer(std::string &text) throw();
      void buffer(std::ostringstream &stream) throw();

      // Interface for Info Log
      void info(const char *text) throw();
      void info(std::string &text) throw();
      void info(std::ostringstream &stream) throw();

      // Interface for Trace log
      void trace(const char *text) throw();
      void trace(std::string &text) throw();
      void trace(std::ostringstream &stream) throw();

      // Interface for Debug log
      void debug(const char *text) throw();
      void debug(std::string &text) throw();
      void debug(std::ostringstream &stream) throw();

      // Error and Alarm log must be always enable
      // Hence, there is no interfce to control error and alarm logs

      // Interfaces to control log levels
      void updateLogLevel(LogLevel logLevel);
      void enableLog();  // Enable all log levels
      void disableLog(); // Disable all log levels, except error and alarm

      // Interfaces to control log Types
      void updateLogType(LogType logType);
      void enableConsoleLogging();
      void enableFileLogging();

      Logger(std::string logFileName);
      ~Logger();

   protected:
      // Log file name. File name should be change from here only
      const std::string logFileName = "MyLogFile.log";

      std::string getCurrentTime();

   private:
      void logIntoFile(std::string &data);
      void logOnConsole(std::string &data);

      Logger() = delete;
      Logger(const Logger &obj) = delete;
      void operator=(const Logger &obj) = delete;

   private:
      static std::unique_ptr<Logger> m_Instance;
      std::ofstream m_File;
      std::mutex mutex;

      LogLevel m_LogLevel;
      LogType m_LogType;
   };

} // End of namespace

#endif // End of _LOGGER_H_
