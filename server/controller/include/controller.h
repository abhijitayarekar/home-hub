#pragma once

#include "homehub.h"
#include "pubsub.h"
#include <thread>
#include "work_manager.h"

using namespace std;

namespace Controller
{

	class Ctrlr : public PubSubCb
	{
	private:
		friend class Worker;

		Ctrlr();
		~Ctrlr();

	public:
		static Ctrlr* getInstance();

		void start();
		void stop();
		
	private:
		void onMessage(const string& message);
		void* subscribeToEvent(string &event);

	private:
		bool m_started;
		WorkManager m_work_manager;
	};
}
