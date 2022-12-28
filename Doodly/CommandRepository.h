#pragma once
/*
	Copyright (C) 2022  Barth.Feudong
	Author can be contacted here: <https://github.com/mrSchaffman/Doodly>

	This file is part of the Doodly project. using the Win32 API and The COM

	Doodly is free software: you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version.

	Doodly is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with this program.  If not, see <https://www.gnu.org/licenses/>.

*/

#include"Command.h"
#include<string>
#include<set>
namespace doodly {
	namespace client_subsystem {
		namespace controller {
			namespace data_abstraction
			{
				class CommandRepository
				{
					class CommandRepositoryImpl;

				public:
					static CommandRepository& getInstance();

					void registerCommand(const std::string& name, abstraction::data_abstraction::command::unique_command_ptr c);
					abstraction::data_abstraction::command::unique_command_ptr deregisterCommand(const std::string& name);
					size_t count() const;
					abstraction::data_abstraction::command::unique_command_ptr getCommandByName(const std::string& name) const;
					bool hasKey(const std::string& s) const;
					std::set<std::string> getAllCommandNames() const;
					void printHelp(const std::string& command, std::ostream&) const;
					void clearAllCommands();

				private:
					CommandRepository();
					~CommandRepository();
					std::unique_ptr<CommandRepositoryImpl> pimpl_;

				private:
					CommandRepository(CommandRepository&) = delete;
					CommandRepository(CommandRepository&&) = delete;
					CommandRepository& operator=(CommandRepository&) = delete;
					CommandRepository& operator=(CommandRepository&&) = delete;
				};

			} // namespace data
		}
	}
}
