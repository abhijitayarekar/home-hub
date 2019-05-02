#pragma once

#include <thread>
#include "pubsub.h"

namespace Controller
{
	class DiscoveryManager : public PubSub
	{
	public:
		DiscoveryManager() : PubSub("disc_man") {}

		~DiscoveryManager(){}

		void start();
		
		void stop();
		
	private:
		void upnp_thread_func();

	private:
		thread m_upnp_thread;
	};
}
