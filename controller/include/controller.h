#pragma once

#include "pubsub.h"
#include <thread>
#include "discovery_manager.h"

using namespace std;

namespace Controller
{
	class Ctrlr : public PubSubCb
	{
	public:
		Ctrlr() {
				m_discoveryManager.addCb(this);
		}

		~Ctrlr() {
			stop();
			m_discoveryManager.removeCb(this);
		}

		void start();
		void stop();
		
	private:
		void onMessage(void* p_msg);

	private:
		bool m_started;
		std::vector<void*> m_workers;
		DiscoveryManager m_discoveryManager;
	};
}
