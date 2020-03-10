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

#include "Log.h"
#include "String.h"

Log::Log() : Singleton<Log>(this)  // RMEM: Log(), 构造函数
{
    setMinimumLogLevel(Notice);
}

Log::~Log()  // RMEM: ~Log(), 析构函数
{
}

Log::Level Log::getMinimumLogLevel()  // RMEM: getMinimumLogLevel()
{
    return m_minimumLogLevel;
}

void Log::setMinimumLogLevel(Log::Level level)  // RMEM: setMinimumLogLevel()
{
    m_minimumLogLevel = level;
}

const char * Log::getIdent() const  // RMEM: getIdent()
{
    return (m_ident);
}

void Log::setIdent(const char *ident)  // RMEM: setIdent()
{
    m_ident = ident;
}

void Log::append(const char *str)  // RMEM: append()
{
    m_outputBuffer << str;

    if (m_outputBuffer.endsWith("\n"))
    {
        write(*m_outputBuffer);
        m_outputBuffer = "";
    }
}

Log & operator << (Log &log, const char *str)  // RMEM: Log 重载运算符 << 
{
    log.append(str);
    return log;
}

Log & operator << (Log &log, int number)  // RMEM: Log 重载运算符 << 
{
    String s = number;
    log.append(*s);
    return log;
}

Log & operator << (Log &log, unsigned number)  // RMEM: Log 重载运算符 << 
{
    String s = number;
    log.append(*s);
    return log;
}

Log & operator << (Log &log, unsigned long number)  // RMEM: Log 重载运算符 << 
{
    String s = number;
    log.append(*s);
    return log;
}

Log & operator << (Log &log, void *ptr)  // RMEM: Log 重载运算符 <<
{
    String s;
    s << Number::Hex << ptr;
    log.append(*s);
    return log;
}
