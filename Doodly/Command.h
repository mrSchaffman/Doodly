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


#include<memory>
namespace abstraction {
	namespace data_abstraction {
		namespace command {
			class Command
			{
			public:
				virtual ~Command() = default;

				void undo() { return undoImpl(); }
				void execute()
				{
					checkPreConditionImpl();
					executeImpl();
					checkPostConditionImpl();
				}
				Command* clone() const { return cloneImpl(); }
				virtual void deallocate() { delete this; }
				const char* getHelpMessage() const { return getHelpMessageImpl(); }

			protected:
				Command() = default;
				Command(const Command&) = default;

				virtual void undoImpl() noexcept = 0;
				virtual void executeImpl() noexcept = 0;
				virtual Command* cloneImpl() const noexcept = 0;

				virtual void checkPostConditionImpl() const {}
				virtual void checkPreConditionImpl() const {}
				virtual const char* getHelpMessageImpl() const noexcept = 0;

			private:
				Command(Command&&) = delete;
				Command& operator=(const Command&) = delete;
				Command& operator=(Command&&) = delete;
			};

			/*
				must go in the Algoritm namespace
			*/
			inline void deallocate(Command* cmd)
			{
				if (cmd)
					cmd->deallocate();
			}

			using unique_command_ptr = std::unique_ptr<Command, decltype(&deallocate)>;

			inline auto make_unique_command_ptr(Command* c)
			{
				return unique_command_ptr{ c, &deallocate };
			}

		}
	}
}