#pragma once
#include <thread>
#include "pubsub.h"

namespace Controller
{
	class Worker : public PubSub {
		public:
			Worker(const string& name) : PubSub(name) {}

			~Worker() {}

			int start() {
				PubSub::start();
				m_thread = std::thread(&Worker::cmd_worker_thread_func, this);
				return 0;
			}

			void stop() {
				PubSub::stop();
				m_thread.join();
			}

		protected:
			virtual void doWork() = 0;

		protected:
			const string m_name;
			std::thread m_thread;
		private:
			void cmd_worker_thread_func() {
				publish(m_name + " Started.");
				doWork();
				publish(m_name + " Stopped.");
			}

	};
}

