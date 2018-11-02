#pragma once

#include <vector>

using namespace std;

namespace Controller
{
	class PubSubCb
	{
	public:
		void onMessage(void* p_msg);
	};

	class PubSub
	{
	public:
		PubSub();
		~PubSub();
		void start();
		void stop();
		void addCb(PubSubCb* p_handler);
		void removeCb(PubSubCb* p_handler);

	private:
		bool m_started;
		vector<PubSubCb*> m_cb;
	};
}
