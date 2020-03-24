#include "work_manager.h"

using namespace Controller;

WorkManager::WorkManager() : PubSub("WorkManager")
{
	m_workers.push_back(new CmdWorker("cmd_worker1"));
	m_workers.push_back(new CmdWorker("cmd_worker2"));
	m_workers[0]->addCb(this);
	m_workers[1]->addCb(this);
}

WorkManager::~WorkManager()
{
	for (CmdWorker* worker : m_workers) {
		worker->stop();
		worker->removeCb(this);
	}
}

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
