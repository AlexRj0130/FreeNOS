/*
 * Copyright (C) 2009 Niek Linnenbank
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

#ifndef __BIN_SH_SHELL
#define __BIN_SH_SHELL

#include <Types.h>
#include <POSIXApplication.h>
#include "ShellCommand.h"

/**
 * @addtogroup bin
 * @{
 */

/**
 * System command shell interpreter
 */
class Shell : public POSIXApplication  // RCLS: Shell : public POSIXApplication，命令行应用
{
  public:

    /**
     * Constructor
     *
     * @param argc Argument count
     * @param argv Argument values
     */
    Shell(int argc, char **argv);  // RMEM: Shell()，构造函数，添加 Shell 应用描述信息，注册 Shell 命令

    /**
     * Destructor
     */
    virtual ~Shell();  // RMEM: ~Shell()，析构函数

    /**
     * Execute the application.
     *
     * @return Result code
     */
    virtual Result exec();  // RMEM: exec()，接口，根据 Shell 的构造参数，选择执行脚本文件或启动交互式 Shell

    /**
     * Get shell command.
     *
     * @param name ShellCommand name.
     * @return ShellCommand object pointer.
     */
    ShellCommand * getCommand(const char *name);  // RMEM:  getCommand(), 公有成员方法，通过名字获取指定 ShellCommand

    /**
     * Get all shell commands.
     *
     * @return HashTable with ShellCommands
     */
    HashTable<String, ShellCommand *> & getCommands();  // RMEM:  getCommands()，公有成员方法，返回 Shell 中已经注册的 m_commands(所有 ShellCommands)

    /**
     * Register a new ShellCommand.
     *
     * @param command ShellCommand object pointer.
     */
    void registerCommand(ShellCommand *command);  // RMEM:  registerCommand(), 公有成员方法，注册 ShellCommand 至 m_commands

  private:

    /**
     * Executes the Shell by entering an infinite loop.
     *
     * @return Result code
     */
    Result runInteractive();  // RMEM:  runInteractive(), 私有成员方法，以交互式方式运行 shell

    /**
     * Executes the given input.
     *
     * @param cmdline Input to execute.
     * @return Exit status of the command.
     */
    int executeInput(char *cmdline);  // RMEM:  executeInput(), 私有成员方法，执行一行 shell 命令，该命令可能来自文件、/bin/目录、以及 shell 输入

    /**
     * Fetch a command text from standard input.
     * @return Pointer to a command text.
     */
    char * getInput();  // RMEM:  getInput(), 私有成员方法，从终端读取输入内容，并对交互过程（编辑、显式等）进行处理

    /**
     * Output a prompt.
     */
    void prompt();  // RMEM:  prompt(), 私有成员方法，显示提示信息（主机名、工作目录等）

    /**
     * Parses an input string into separate pieces.
     * @param cmdline Command input string.
     * @param argv Argument list buffer.
     * @param maxArgv Maximum number of entries in argv.
     * @param background True if process must run in the background.
     * @return Number of parsed arguments.
     */
    Size parse(char *cmdline, char **argv, Size maxArgv, bool *background);  // RMEM:  parse(), 私有成员方法

  private:

    /** All known ShellCommands. */
    HashTable<String, ShellCommand *> m_commands;  // RMEM:  m_commands, 私有成员变量，用来存储 ShellCommand 实例
};

/**
 * @}
 */

#endif /* __BIN_SH_SHELL */
