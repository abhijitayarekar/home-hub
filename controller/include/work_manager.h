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

		~WorkManager(){}

		void start() {
			PubSub::start();

			publish(m_name + " Started.");
		}
		
		void stop() {
			m_workers[0]->removeCb(this);
			m_workers[1]->removeCb(this);
			PubSub::stop();
			publish(m_name + " Stopped.");
		}

	private:
		void onMessage(const string& message) {
			cout << message << endl;
		}

	private:
		std::vector<CmdWorker*> m_workers;
	};
}
