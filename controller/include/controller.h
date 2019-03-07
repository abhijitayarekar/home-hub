#pragma once

#include "pubsub.h"
#include <thread>
#include "discovery_manager.h"
#include "work_manager.h"

using namespace std;

namespace Controller
{
	class Ctrlr : public PubSubCb
	{
	public:
		Ctrlr() {
				m_discovery_manager.addCb(this);
				m_work_manager.addCb(this);
		}

		~Ctrlr() {
			stop();
			m_discovery_manager.removeCb(this);
			m_work_manager.removeCb(this);
		}

		void start();
		void stop();
		
	private:
		void onMessage(void* p_msg);

	private:
		bool m_started;
		DiscoveryManager m_discovery_manager;
		WorkManager m_work_manager;
	};
}
