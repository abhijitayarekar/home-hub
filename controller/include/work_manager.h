#pragma once
#include "cmd_worker.h"

namespace Controller
{
	class WorkManager : public PubSub, PubSubCb
	{
	public:
		WorkManager() : PubSub("work_man") {
			m_workers.push_back(new CmdWorker("cmd_worker1"));
			m_workers.push_back(new CmdWorker("cmd_worker2"));
			m_workers[0]->addCb(this);
			m_workers[1]->addCb(this);
		}

		~WorkManager(){
			for (CmdWorker* worker : m_workers) {
				worker->stop();
				worker->removeCb(this);
			}
		}

		void start();
		
		void stop();

	private:
		void onMessage(const string& message);

	private:
		std::vector<CmdWorker*> m_workers;
	};
}
