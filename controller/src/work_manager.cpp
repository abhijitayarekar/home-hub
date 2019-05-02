#include "work_manager.h"

using namespace Controller;

void WorkManager::start()
{
	PubSub::start();

	for (CmdWorker* worker : m_workers) {
		worker->start();
	}
	publish(m_name + " Started.");
}

void WorkManager::stop()
{
	for (CmdWorker* worker : m_workers) {
		worker->stop();
	}

	PubSub::stop();
	publish(m_name + " Stopped.");
}

void WorkManager::onMessage(const string& message)
{
	cout << message << endl;
}
