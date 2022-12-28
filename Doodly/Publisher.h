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

#include"IService.h"
#include"Observer.h"
namespace service_system {
	namespace publisher {
		class Publisher : public abstraction::logic::service::IService
		{
			static const std::string name;
			class PublisherImpl;

		public:
			Publisher();
			void subscribe(const std::string& eventName, std::unique_ptr<abstraction::boundary::proxy::Observer> observer);
			void unsubscribe(const std::string& eventName, const std::string& observerName);
			std::string getName() const noexcept override { return name; }
			const std::string getServiceDescription() const override { return "This Class is used for subscription"; }
			const std::string getServiceLocalisation() const override { return "Located somewhere"; }
			abstraction::data_abstraction::OutputData* transform(std::shared_ptr<abstraction::data_abstraction::InputData> f) override
			{
				return nullptr;
			};

			virtual ~Publisher();
			void notify(const std::string& eventName, std::shared_ptr<abstraction::data_abstraction::Data>) const;
			void registerEvent(const std::string& eventName);

		private:
			std::unique_ptr<PublisherImpl> impl;
		};
	}
}