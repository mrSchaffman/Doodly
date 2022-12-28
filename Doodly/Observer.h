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


#include"Data.h"
#include<string>
#include<memory>
namespace boundary {
	namespace user_interaction {
		namespace proxy {
			class Observer
			{
			public:
				Observer(const std::string& n) : name{ n } {}
				const std::string& getName() const { return name; }
				virtual void notify(std::shared_ptr<abstraction::data_abstraction::Data> d) { notifyImpl(d); };
				virtual ~Observer() = default;

			private:
				virtual void notifyImpl(std::shared_ptr<abstraction::data_abstraction::Data> d) = 0;

			private:
				std::string name;
			};
		}
	}
}