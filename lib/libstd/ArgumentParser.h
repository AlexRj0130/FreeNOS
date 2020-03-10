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

#ifndef __LIBSTD_ARGUMENTPARSER_H
#define __LIBSTD_ARGUMENTPARSER_H

#include "Types.h"
#include "Macros.h"
#include "String.h"
#include "HashTable.h"
#include "Vector.h"
#include "Argument.h"
#include "ArgumentContainer.h"

/**
 * @addtogroup lib
 * @{
 *
 * @addtogroup libstd
 * @{
 */

/**
 * Generic command-line argument parser.
 */
class ArgumentParser  // RCLS: 应用程序参数解析器（Application的私有成员）
{
  public:

    /**
     * Result codes.
     */
    enum Result  // RMEM: Result，参数解析器的返回值
    {
        Success,
        InvalidArgument,
        NotFound,
        AlreadyExists
    };

  public:

    /**
     * Constructor
     */
    ArgumentParser();  // RMEM: ArgumentParser(), 构造函数

    /**
     * Destructor
     */
    virtual ~ArgumentParser();  // RMEM: ~()ArgumentParser()，析构函数

    /**
     * Get program usage.
     *
     * @return Program usage string reference.
     */
    String getUsage() const;  // RMEM: getUsage()，公有成员方法，获取参数信息，包括参数名、程序名等

    /**
     * Retrieve program name.
     *
     * @return Program name
     */
    const String & name() const;  // RMEM: name()，公有成员方法，获取 m_name

    /**
     * Set program name.
     *
     * @param name Program name string.
     */
    void setName(const char *name);  // RMEM: setName()，公有成员方法，设置 m_name

    /**
     * Set program description.
     *
     * @param desc Program description string.
     */
    void setDescription(const String & desciption);  // RMEM: setDescription()，公有成员方法，设置 m_Description

    /**
     * Register a flag Argument
     *
     * @param arg Argument identifier
     * @param name Argument name
     * @param description Argument single line description
     *
     * @return Result code.
     */
    Result registerFlag(char arg,
                        const char *name,
                        const char *description);  // RMEM: registerFlag()，公有成员方法，注册参数选项、参数名、描述信息

    /**
     * Register a positional argument.
     *
     * @param name Argument name
     * @param description Argument single line description
     * @param count Maximum number to set for this positional argument
     *
     * @return Result code.
     */
    Result registerPositional(const char *name,
                              const char *description,
                              Size count = 1);  // RMEM: registerPositional()，公有成员方法，注册参数名、描述信息

    /**
     * Parse input arguments.
     *
     * This function parses the given arguments and
     * fills the argument container with parsed arguments.
     *
     * @param argc Input argument count.
     * @param argv Input argument values.
     * @param output Filled with parsed arguments on output.
     *
     * @return Result code.
     */
    Result parse(int argc,
                 char **argv,
                 ArgumentContainer & output);  // RMEM: parse()，公有成员方法，解析命令行参数至 ArgumentContainer

  private:

    /** Contains all registered flag arguments by name. */
    HashTable<String, Argument *> m_flags;  // RMEM: m_flags，私有成员变量

    /** Contains all registered flag arguments by single character identifier. */
    HashTable<String, Argument *> m_flagsId;  // RMEM: m_flagsId，私有成员变量

    /** Contains all registered positional arguments. */
    Vector<Argument *> m_positionals;  // RMEM: m_positionals，私有成员变量

    /** Program name */
    String m_name;  // RMEM: m_name，私有成员变量

    /** Program description */
    String m_description;  // RMEM: m_description，私有成员变量
};

/**
 * @}
 * @}
 */

#endif /* __LIBSTD_ARGUMENTPARSER_H */
