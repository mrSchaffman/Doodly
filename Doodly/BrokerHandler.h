#pragma once
#include"IService.h"
#include<unordered_map>
namespace broker_system {
	namespace white_space {
		class BrokerHandler
		{
		public:
			static BrokerHandler& getInstance()
			{
				static BrokerHandler instance;
				return instance;
			}
			~BrokerHandler() = default;
			bool registerService(std::shared_ptr<abstraction::logic::service::IService> s) noexcept;
			std::shared_ptr<abstraction::logic::service::IService> getService(const std::string& serviceName) const noexcept;
		private:
			BrokerHandler();


		private:
			std::unordered_map<std::string, std::shared_ptr<abstraction::logic::service::IService>> m_services;

		private:
			BrokerHandler(const BrokerHandler&) = delete;
			BrokerHandler(BrokerHandler&&) = delete;
			BrokerHandler& operator=(const BrokerHandler&) = delete;
			BrokerHandler& operator=(BrokerHandler&&) = delete;
		};
	}
}
