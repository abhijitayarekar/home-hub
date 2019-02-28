#pragma once
#include <iostream>
#include <chrono>
#include <iomanip>

namespace Controller
{
	class DiscoveryManager : public PubSub
	{
	public:
		DiscoveryManager() : PubSub("disc_man") {}

		~DiscoveryManager(){}

		void start() {
			PubSub::start();
			m_upnp_thread = std::thread(&DiscoveryManager::upnp_thread_func, this);
		}
		
		void stop() {
			PubSub::stop();
			m_upnp_thread.join();
		}
		
	private:
		void upnp_thread_func() {
			while (m_started) {
				auto t = std::time(nullptr);
				auto tm = *std::localtime(&t);
				cout << m_name << " : upnp : Sleeping : " << std::put_time(&tm, "%d-%m-%Y %H-%M-%S")<<endl;
				std::this_thread::sleep_for(std::chrono::seconds(1));
			}
		}

	private:
		thread m_upnp_thread;
	};
}
