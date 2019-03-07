#pragma once

namespace Controller
{
	class WorkManager : public PubSub
	{
	public:
		WorkManager() : PubSub("work_man") {}

		~WorkManager(){}

		void start() {
			PubSub::start();
		}
		
		void stop() {
			PubSub::stop();
		}
	private:
		std::vector<void*> m_workers;
	};
}
