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
#include <unordered_map>

namespace qz
{
	namespace utils
	{
		constexpr std::size_t MaxArgumentNumber = 10;
		using function_t = std::function<int(
		    std::array<std::string, MaxArgumentNumber>&& args)>;
		
		/**
		 * @brief The command structure stores information about a command
		 */

		struct Command
		{
			std::string name;
			std::string help;
			std::string permission;
			function_t function;

			Command() {}
		};

		/**
		 * @brief The command book stores commands and information on them to be
		 * used by a commander
		 */

		struct CommandBook
		{
			using Commands_t = std::unordered_map<std::string, Command>;
			Commands_t m_commands;

			/**
			 * @brief Registers a command in the command registry
			 *
			 * @param command The keyword for calling the command
			 * @param permission What permission is required to run this command
			 */
			void add(const std::string& command, const std::string& help,
			         const std::string& permission, function_t f);

			/**
			 * @brief Searches for a command and returns the iterator
			 *
			 * @param command The command to search for
			 */
			Commands_t::iterator find(const std::string& command);

		private:
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
			 */
			int run(const std::string&                           command,
			        std::array<std::string, MaxArgumentNumber>&& args);

			/**
			 * @brief Returns helpstring for command
			 *
			 * @param args array of input, args[0] is the command helpstring is
			 * returned for
			 */
			int help(
			    std::array<std::string, qz::utils::MaxArgumentNumber>&& args);

			/**
			 * @brief Returns string listing available commands
			 */
			int list();

			/**
			 * @brief Listens for commands.
			 */
			int post();
		};
	}; // namespace utils
} // namespace qz
