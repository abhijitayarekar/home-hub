#pragma once

#include <zmq.hpp>
#include "pubsub.h"

using namespace std;

namespace Controller
{

	class Ctrlr : public PubSubCb
	{
	public:
		Ctrlr();
		~Ctrlr();
		void start();
		void stop();
		
	private:
		void onMessage(void* p_msg);

	private:
		zmq::context_t m_context;
		zmq::socket_t m_localWorkerSocket;
		bool m_started;
		PubSub m_pubsub;
		std::vector<Worker*> m_localWorkers;
	};
}
