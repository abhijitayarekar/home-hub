#include "work_manager.h"

using namespace Controller;

WorkManager::WorkManager(int num_workers) : PubSub("WorkManager"), ctx_(1),
														 frontend_(ctx_, ZMQ_ROUTER),
														 backend_(ctx_, ZMQ_DEALER)
{
	CmdWorker *worker;
	int i;

	frontend_.bind("tcp://*:5570");
	backend_.bind("inproc://backend");

	for (i = 0; i < num_workers; i++) {
		worker = new CmdWorker("cmd_worker" + i);
		if (!worker)
			continue;

		worker->addCb(this);
		m_workers.push_back(worker);
		n_workers++;
	}
}

WorkManager::~WorkManager()
{
	for (CmdWorker* worker : m_workers) {
		worker->stop();
		worker->removeCb(this);
		delete worker;
	}

	frontend_.unbind("tcp://*:5570");
	backend_.unbind("tcp://*:5571");
}

void WorkManager::start()
{
	PubSub::start();

	for (CmdWorker* worker : m_workers)
		worker->start();

	zmq::proxy((void*)frontend_, (void*)backend_, nullptr);

	publish(m_name + " Started.");
}

void WorkManager::stop()
{
	for (CmdWorker* worker : m_workers)
		worker->stop();

	PubSub::stop();
	publish(m_name + " Stopped.");
}

void WorkManager::onMessage(const string& message)
{
	cout << message << endl;
}
