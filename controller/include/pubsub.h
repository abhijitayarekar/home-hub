#pragma once

#include <vector>
#include <string>

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
		PubSub() : m_name(std::move("")) {}
		PubSub(string name) : m_name(std::move(name)) {}
		~PubSub();
		void start();
		void stop();
		virtual void addCb(PubSubCb* p_handler);
		virtual void removeCb(PubSubCb* p_handler);

	protected:
		string m_name;
		bool m_started;
		vector<PubSubCb*> m_cb;
	};
}
