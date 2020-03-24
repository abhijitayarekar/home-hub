#pragma once
#include "cmd_worker.h"

namespace Controller
{
	class WorkManager : public PubSub, PubSubCb
	{
	public:
		WorkManager();

		~WorkManager();

		void start();
		
		void stop();

	private:
		void onMessage(const string& message);

	private:
		std::vector<CmdWorker*> m_workers;
	};
}
