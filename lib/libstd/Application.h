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

#ifndef __LIBSTD_APPLICATION_H
#define __LIBSTD_APPLICATION_H

#include "Types.h"
#include "Macros.h"
#include "Log.h"
#include "ArgumentParser.h"
#include "ArgumentContainer.h"

/**
 * @addtogroup lib
 * @{
 *
 * @addtogroup libstd
 * @{
 */

/**
 * Generic application
 */
class Application // RCLS: Application，所有程序的（纯虚）基类，接口为 run
{
  private:

    /** Exit code for successful termination */
    static const uint ExitSuccess = 0;

    /** Exit code for failure termination */
    static const uint ExitFailure = 1;

  public:

    /**
     * Result codes.
     */
    enum Result  // RMEM: Result，程序的执行结果，是个枚举值
    {
        Success,
        NotFound,
        IOError,
        InvalidArgument,
        ShowUsage
    };

  public:

    /**
     * Class constructor.
     *
     * @param argc Argument count
     * @param argv Argument values
     */
    Application(int argc, char **argv);  // RMEM: Application()，构造函数，程序待执行的参数

    /**
     * Class destructor.
     */
    virtual ~Application(); // RMEM: ~Application()，析构函数

    /**
     * Run the application
     *
     * @return Exit code
     */
    virtual int run();  // RMEM: run()，接口，运行

  protected:

    /**
     * Initialize the application.
     *
     * @return Result code
     */
    virtual Result initialize();  // RMEM: initialize()，子类接口，初始化

    /**
     * Execute the application event loop.
     *
     * @return Result code
     */
    virtual Result exec() = 0; // RMEM: exec()，子类接口，执行

    /**
     * Print text to output.
     *
     * @param string Text to print to program output.
     * @return Result code.
     */
    virtual Result output(const char *string) const = 0;  // RMEM: output()，子类接口，输出文本内容

    /**
     * Print string to output.
     *
     * @param string Reference to string to output.
     *
     * @return Result code.
     */
    virtual Result output(String & string) const;  // RMEM: output()，子类接口，输出文本内容

  protected:

    /**
     * Get program arguments parser.
     *
     * @return Program arguments parser.
     */
    ArgumentParser & parser();  // RMEM: parser()，子类成员方法，获取参数解析器

    /**
     * Get constant program arguments parser.
     *
     * @return Program arguments parser.
     */
    const ArgumentParser & parser() const;  // RMEM: parser()，子类成员方法，获取参数解析（常量）

    /**
     * Get program arguments.
     */
    const ArgumentContainer & arguments() const;  // RMEM: arguments()，子类成员方法，获取参数容器

    /**
     * Set program version.
     *
     * @param version Program version string
     */
    void setVersion(const String & version);  // RMEM: setVersion()，子类成员方法，设置程序的版本号

  private:

    /**
     * Print usage and terminate.
     */
    void usage() const;  // RMEM: usage()，私有成员方法，显示程序的使用方法

  private:

    /** Program argument parser object */
    ArgumentParser m_parser;  // RMEM: m_parser，私有成员变量，参数解析器

    /** Parsed Arguments */
    ArgumentContainer m_arguments;  // RMEM: m_arguments，私有成员变量，参数容器

    /** Input argument count */
    int m_argc;  // RMEM: m_argc，私有成员变量，参数计数

    /** Input argument values */
    char ** m_argv;  // RMEM: m_argv，私有成员变量，参数

    /** Program version */
    String m_version;  // RMEM: m_version，私有成员变量，参数
};

/**
 * @}
 * @}
 */

#endif /* __LIBSTD_APPLICATION_H */
