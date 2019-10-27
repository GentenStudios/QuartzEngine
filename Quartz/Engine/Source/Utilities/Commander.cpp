// Copyright 2019 Genten Studios
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
//
// 1. Redistributions of source code must retain the above copyright notice,
// this list of conditions and the following disclaimer.
//
// 2. Redistributions in binary form must reproduce the above copyright notice,
// this list of conditions and the following disclaimer in the documentation
// and/or other materials provided with the distribution.
//
// 3. Neither the name of the copyright holder nor the names of its contributors
// may be used to endorse or promote products derived from this software without
// specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
// ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
// LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
// CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
// SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
// INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
// CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
// ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
// POSSIBILITY OF SUCH DAMAGE.

#include <Quartz/Utilities/Commander.hpp>
#include <iostream>
#include <utility>

using namespace qz::utils;

Commands_t::iterator CommandBook::find(const std::string& command)
{
	return m_commands.find(command);
}

void CommandBook::add(const std::string& command, const std::string& help,
                     const std::string& permission, function_t f)
{
	m_commands[command] = Command();
	m_commands[command].command = command;
	m_commands[command].help = help;
	m_commands[command].permission = permission;
	m_commands[command].function = std::move(f)
}

Commander::Commander(CommandBook& book, std::ostream& out, std::istream& in)
    : m_book(book), m_out(out), m_in(in)
{}

Commander::~Commander()
{}

int Commander::help(std::array<std::string, qz::utils::MaxArgumentNumber>&& args)
{
	if (args[0] == "")
	{
		m_out << "Type /help [command] to learn more about a command \nType "
		         "/list for a list of available commands\n";
		return 1;
	}
	else if (args[0] == "help")
	{
		m_out << "Type /help [command] to learn more about a command \n";
		return 1;
	}
	else if (args[0] == "list")
	{
		m_out << "Lists available commands\n";
		return 1;
	}

	CommandBook::Commands_t::iterator j = m_book.find(args[0]);
	if (j == CommandBook::Commands_t::end())
	{
		m_out << "Command \"" << args[0] << "\" not found \n";
		return -1;
	}
	else
	{
		m_out << j->second.help;
		return 1;
	}
}

int Commander::run(const std::string&                           command,
                   std::array<std::string, MaxArgumentNumber>&& args)
{
	// Check for built in functions
	if (command == "help")
	{
		return this->help(std::move(args));
	}
	else if (command == "list")
	{
		return this->list();
	}

	// If no built in functions match, search library
	CommandBook::Commands_t::iterator j = m_book.find(command);
	if (j == CommandBook::Command_t::end())
	{
		m_out << "Command \"" << command << "\" not found \n";
		return -1;
	}
	else
	{
		return j->second.function(std::move(args));
	}
}

int Commander::list()
{
	m_out << "Available commands\n";
	for (auto&& command: m_book.m_commands)
	{
		m_out << "- " << command.first << "\n";
	}
	return 1;
}

int Commander::post()
{
	std::string input;
	while (true)
	{
		m_out << "\n->";
		int                                        i = 0;
		std::array<std::string, MaxArgumentNumber> args;
		std::string                                command = "";
		std::string                                buffer;
		m_in >> command;

		while (m_in.peek() != '\n' && i <= MaxArgumentNumber)
		{
			m_in >> buffer;
			args[i] = buffer;
			i++;
		}

		if (command == "exit")
		{
			break;
		}
		run(command, std::move(args));
	}
	return 0;
}