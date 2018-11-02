#pragma once
#include <zmq.hpp>
#include <thread>

namespace Controller
{
	class LocalWorkHandler : public Worker {
		public:
			LocalWorkHandler(zmq::context_t &zm_ctx) :
					 m_zm_ctx(zm_ctx),
					 m_zm_socket(m_ctx, ZMQ_DEALER) {
					 	
					 }

			~LocalWorkHandler() {
			}

			void doWork() {
				m_worker.connect("inproc://local_work");

				try {
					while (m) {
						zmq::message_t identity;
						zmq::message_t msg;
						zmq::message_t copied_id;
						zmq::message_t copied_msg;
						m_worker.recv(&identity);
						m_worker.recv(&msg);

						int replies = within(5);
						for (int reply = 0; reply < replies; ++reply) {
							s_sleep(within(1000) + 1);
							copied_id.copy(&identity);
							copied_msg.copy(&msg);
							m_worker.send(copied_id, ZMQ_SNDMORE);
							m_worker.send(copied_msg);
						}
					}
				} catch (std::exception &e) {
					cout << e.what();
				}
			}

		protected:
			zmq::context_t &m_zm_ctx;
			zmq::socket_t m_zm_socket;
			char m_identity[16];
	};
}

