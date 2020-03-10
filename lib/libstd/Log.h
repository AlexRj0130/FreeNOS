/*
 * Copyright (C) 2015 Niek Linnenbank
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef _LOG_H
#define _LOG_H

#include "Singleton.h"
#include "Macros.h"
#include "String.h"

/**
 * @addtogroup lib
 * @{
 *
 * @addtogroup libstd
 * @{
 */

/**
 * Output a log line to the system log (syslog).
 *
 * @param type Log level
 * @param typestr Log level string
 * @param msg Message to output
 */
#define MAKE_LOG(type, typestr, msg) \
    {\
     if (Log::instance && type <= Log::instance->getMinimumLogLevel())  \
        (*Log::instance) << "[" typestr "] " << __FILE__ ":" <<  __LINE__ << " " << __FUNCTION__ << " -- " << msg << "\r\n"; \
    }

/** Action to take after printing a fatal error message */
#ifndef FATAL_ACTION
#define FATAL_ACTION for (;;);
#endif /* FATAL_ACTION */

/**
 * Output a critical message and terminate program immediatly.
 *
 * @param msg The critical message.
 */
#define FATAL(msg) \
    { \
        MAKE_LOG(Log::Emergency, "Emergency", msg); \
        { FATAL_ACTION } \
    }

/**
 * Output an error message.
 *
 * @param msg The error message.
 */
#define ERROR(msg)   MAKE_LOG(Log::Error, "Error", msg)

/**
 * Output a warning message.
 *
 * @param msg The warning message.
 */
#define WARNING(msg) MAKE_LOG(Log::Warning, "Warning", msg)

/**
 * Output a notice message.
 *
 * @param msg The notice message
 */
#define NOTICE(msg)  MAKE_LOG(Log::Notice, "Notice", msg)

/**
 * Output a regular message to standard output.
 *
 * @param msg The information message
 */
#define INFO(msg)    MAKE_LOG(Log::Info, "Info", msg)

/**
 * Output a debug message to standard output.
 *
 * @param msg The debug message to output
 */
#define DEBUG(msg)   MAKE_LOG(Log::Debug, "Debug", msg)

/**
 * Logging class.
 *
 * @note This class is a singleton
 */
class Log : public Singleton<Log>  // RCLS: Log: public Singleton<Log>，输出日志
{
  public:

    /** Logging level values */
    enum Level  // RMEM: Level，日志级别，枚举类型
    {
        Emergency,
        Alert,
        Critical,
        Error,
        Warning,
        Notice,
        Info,
        Debug
    };

  public:

    /**
     * Constructor.
     */
    Log();  // RMEM: Log()，构造函数，设置日志的默认级别

    /**
     * Destructor
     */
    virtual ~Log();  // RMEM: ~Log()，析构函数

    /**
     * Get the minimum logging level.
     *
     * @return Minimum LogLevel
     */
    Level getMinimumLogLevel();  // RMEM: getMinimumLogLevel()，公有成员方法，获取日志级别

    /**
     * Set the minimum logging level.
     */
    void setMinimumLogLevel(Level level);  // RMEM: setMinimumLogLevel()，公有成员方法，设置日志级别

    /**
     * Append to buffered output.
     *
     * @param str String to append to buffer
     */
    void append(const char *str);  // RMEM: append()，公有成员方法，将指定内容追加到输出缓冲区 m_outputBuffer

    /**
     * Set log identity.
     *
     * @param ident Log identity
     */
    void setIdent(const char *ident);  // RMEM: setIdent()，公有成员方法

    /**
     * Retrieve log identify.
     *
     * @return Log identity
     */
    const char * getIdent() const;  // RMEM: getIdent()，公有成员方法 

  protected:

    /**
     * Write to the actual output device.
     */
    virtual void write(const char *str) = 0;  // RMEM: write(), 子类接口，具体决定如何把内容写入输出缓冲器 m_outputBuffer

  private:

    /** Minimum log level required to log. */
    Level m_minimumLogLevel;  // RMEM: m_minimumLogLevel，私有成员变量

    /** Identity */
    const char *m_ident;  // RMEM: m_ident，私有成员变量

    /** Buffered output */
    String m_outputBuffer;  // RMEM: m_outputBuffer, 私有成员变量
};

/**
 * @name Operators to output various standard types to the log
 * @{
 */

Log & operator << (Log &log, const char *str);

Log & operator << (Log &log, int number);

Log & operator << (Log &log, unsigned number);

Log & operator << (Log &log, unsigned long number);

Log & operator << (Log &log, void *ptr);

/**
 * @}
 */

/**
 * @}
 * @}
 */

#endif /* _LOG_H */
