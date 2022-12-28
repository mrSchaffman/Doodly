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
namespace service_system {
	namespace tokenizer {
		namespace logic {
			namespace service {
				class TokenizerService : public abstraction::logic::service::IService
				{
					static const std::string name; // = "tokenizer";
				public:
					TokenizerService() = default;

					std::string getName() const noexcept override { return name; }
					const std::string getServiceDescription() const override { return "tokenize the string"; }
					const std::string getServiceLocalisation() const override { return "located somewhere"; }

					abstraction::data_abstraction::OutputData* transform(std::shared_ptr<abstraction::data_abstraction::InputData> d) override;
					~TokenizerService();

				private:
					TokenizerService(const TokenizerService&) = delete;
					TokenizerService(TokenizerService&&) = delete;
					TokenizerService& operator=(const TokenizerService&) = delete;
					TokenizerService& operator=(TokenizerService&&) = delete;
				};
			}
		}
	}
}