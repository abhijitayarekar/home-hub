#pragma once

#include <zmq.hpp>
#include "pubsub.h"
#include <thread>

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
		void localConnThreadFunc();

	private:
		thread m_localConnThread;
		zmq::context_t m_context;
		zmq::socket_t m_localConnSocket;
		bool m_started;
		PubSub m_pubsub;
		std::vector<void*> m_localConns;
	};
}
