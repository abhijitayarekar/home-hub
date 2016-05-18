#pragma once

namespace Controller
{
	enum {
		WORKER_TYPE_UNKNOWN=0,
		WORKER_TYPE_NET,
		WORKER_TYPE_ZIGBEE,
		WORKER_TYPE_ZWAVE
	} WorkerType_t;

	class Worker {
		public:
			Worker(zmq::context_t &ctx, int i_sockType)
				: m_ctx(ctx), m_worker(m_ctx, i_sockType)
			 {}

			~Worker() {
			}

			void work();

		protected:
			WorkerType_t m_type;
			zmq::context_t &m_ctx;
			zmq::socket_t m_worker;
			char m_identity[16];
	};
}

