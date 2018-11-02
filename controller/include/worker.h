#pragma once
#include <zmq.hpp>

namespace Controller
{
	class Worker {
		public:
			Worker() : m_active(false) {
			}

			~Worker() {
			}

			int start() {
				if (m_active)
					return 0;

				m_active = true;
				m_thread = std::thread(thread_func);
				return 0;
			}

			void stop() {
				if (!m_active)
					return 0;

				m_active = false;
				m_thread.join();
				return 0;
			}

		protected:
			virtual void doWork() = 0;

			void thread_func() {
				while (m_active) {
					doWork();
				}
			}

		protected:
			bool m_active;
			std:thread m_thread;
	};
}

