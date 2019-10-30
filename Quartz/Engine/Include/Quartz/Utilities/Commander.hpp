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

#pragma once

#include <array>
#include <functional>
#include <string>

namespace qz
{
	namespace utils
	{
		constexpr std::size_t MAX_COMMANDS_NUMBER  = 100;
		constexpr std::size_t MAX_ARGUMENTS_NUMBER = 10;
		typedef std::function<void(
		    std::array<std::string, MAX_ARGUMENTS_NUMBER> args)>
		    function;

		/**
		 * @brief The command book stores commands and information on them to be
		 * used by a commander
		 */

		struct CommandBook
		{
			std::array<std::string, MAX_COMMANDS_NUMBER> m_command;
			std::array<std::string, MAX_COMMANDS_NUMBER> m_help;
			std::array<std::string, MAX_COMMANDS_NUMBER> m_permission;
			std::array<function, MAX_COMMANDS_NUMBER>    m_functions;

			/**
			 * @brief Registers a command in the command registry
			 *
			 * @param command The keyword for calling the command
			 * @param permission What permission is required to run this command
			 */
			void add(const std::string& command, const std::string& help,
			         const std::string& permission, function f);

			/**
			 * @brief Searches for a command
			 *
			 * @param command The command to search for
			 * @return index command is located at or -1 if its not found
			 */
			int find(const std::string& command);

			/**
			 * @brief Gets next open space in book
			 *
			 * @return Returns the next open space in arrays as an integer
			 */
			int getPage();

		private:
			/**
			 * @brief Counter that keep track of next space in the arrays (eg
			 * next page in the book)
			 */
			int m_page;
		};

		/**
		 * @brief The Commander handles comand line functions. It accepts an in
		 * and out stream on creation and can interact with the command line or
		 * another interface.
		 *
		 */
		class Commander
		{
		private:
			CommandBook   m_book;
			std::ostream& m_out;
			std::istream& m_in;

		public:
			/**
			 * @brief Initializes a commander that can run and execute commands
			 *
			 * @param book The command book that the commander uses to route
			 * commands to functions
			 * @param out An output stream the commander outputs results to
			 * @param in An input stream the commander accepts input to
			 */
			Commander(CommandBook& book, std::ostream& out, std::istream& in);
			~Commander();

			/**
			 * @brief Calls a command
			 *
			 * @param command The keyword for calling the command.
			 * @return Returns True if the function was called and False if the
			 * function could not be found
			 */
			bool run(
			    const std::string&                                    command,
			    const std::array<std::string, MAX_ARGUMENTS_NUMBER>&& args);

			/**
			 * @brief Returns helpstring for command
			 *
			 * @param args array of input, args[0] is the command helpstring is
			 * returned for, all other array values are not used
			 * @return Returns True if successful and False if it could not find
			 * the innputted command
			 */
			bool help(const std::array<std::string,
			                           qz::utils::MAX_ARGUMENTS_NUMBER>&& args);

			/**
			 * @brief Returns string listing available commands
			 */
			void list();

			/**
			 * @brief Listens for commands.
			 */
			void post();
		};
	}; // namespace utils
} // namespace qz
