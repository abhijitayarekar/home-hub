#pragma once
#include <thread>
#include <mutex>
#include "pubsub.h"

namespace Controller
{
	class Worker : public PubSub {
		public:
			Worker(const string& name) : PubSub(name) {}

			~Worker() {
				stop();
			}

			int start() {
				PubSub::start();
				m_thread = std::thread(&Worker::cmd_worker_thread_func, this);
				return 0;
			}

			void stop() {
				PubSub::stop();
				if (m_thread.joinable())
					m_thread.join();
			}

			void procesMsg(json& msg) {

			}

		protected:
			virtual void doWork() = 0;

		protected:
			std::thread m_thread;
			std::mutex m_msg_mutex;

		private:
			void cmd_worker_thread_func() {
				publish(m_name + " Started.");
				doWork();
				publish(m_name + " Stopped.");
			}

	};
}

