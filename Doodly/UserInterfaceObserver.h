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

#include"Observer.h"
#include"CommandDispatcher.h"
namespace doodly {
	namespace client_subsystem {
		namespace view {
			namespace proxy {
				class UserInterfaceObserver : public abstraction::boundary::proxy::Observer
				{
				public:
					explicit UserInterfaceObserver(controller::control::state_dependent_control::CommandDispatcher& ce)
						: Observer{ "UserInterfaceObserver" },
						m_ce{ ce }
					{};

				private:
					void notifyImpl(std::shared_ptr<abstraction::data_abstraction::Data>) override;

					controller::control::state_dependent_control::CommandDispatcher& m_ce;
				};
			}
		}
	}
}
