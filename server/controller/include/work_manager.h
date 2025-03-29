#pragma once

#include <zmq.hpp>
#include <zhelpers.hpp>

#include "cmd_worker.h"

namespace Controller
{
	class WorkManager : public PubSub, PubSubCb
	{
	public:
		WorkManager(int num_workers = 5);

		~WorkManager();

		void start();
		
		void stop();

	private:
		void onMessage(const string& message);

	private:
		std::vector<CmdWorker*> m_workers;
		zmq::context_t ctx_;
		zmq::socket_t frontend_;
		zmq::socket_t backend_;
		int n_workers;
	};
}
