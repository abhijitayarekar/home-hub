#include <thread>
#include "worker.h"

using namespace Controller;

int Worker::start()
{
	PubSub::start();
	m_thread = std::thread(&Worker::cmd_worker_thread_func, this);
	return 0;
}

void Worker::stop()
{
	PubSub::stop();
	if (m_thread.joinable())
		m_thread.join();
}

void Worker::procesMsg(HhJson* msg)
{

}

void Worker::cmd_worker_thread_func()
{
	publish(m_name + " Started.");
	doWork();
	publish(m_name + " Stopped.");
}
