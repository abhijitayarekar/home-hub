#pragma once
#include <thread>
#include <mutex>
#include "pubsub.h"
#include "hh_json.h"

namespace Controller
{
	class Worker : public PubSub {
		public:
			Worker(const string& name);

			~Worker();

			int start();

			void stop();

			void procesMsg(HhJson* msg);

		protected:
			virtual void doWork() = 0;

		protected:
			std::thread m_thread;
			std::mutex m_msg_mutex;

		private:
			void cmd_worker_thread_func();
	};
}

