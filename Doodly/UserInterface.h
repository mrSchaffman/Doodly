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

#include"Publisher.h"
#include"IUserInteraction.h"
namespace doodly {
	namespace client_subsystem {
		namespace view {
			namespace boundary {
				namespace user_interaction {
					class UserInterface : public abstraction::boundary::user_interaction::IUserInteraction, protected service_system::publisher::Publisher
					{
					public:
						static const char* InputEntered;

					public:
						UserInterface() { Publisher::registerEvent(InputEntered); }
						virtual ~UserInterface() = default;
						// virtual void sendInput() override;
						// virtual void sendOutput(const char *) override;

					public:
						using Publisher::notify;
						using Publisher::subscribe;
						using Publisher::unsubscribe;
					};
				}
			}
		}
	}
}
