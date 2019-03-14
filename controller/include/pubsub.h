#pragma once

#include <vector>
#include <string>

using namespace std;

namespace Controller
{
	class PubSubCb
	{
	public:
		virtual void onMessage(const string& messsage) = 0;
	};

	class PubSub
	{
	public:
		//PubSub() : m_name(std::move("")) {}
		PubSub(const string& name) : m_name(name) {}
		~PubSub();
		void start();
		void stop();
		void addCb(PubSubCb* p_handler);
		void removeCb(PubSubCb* p_handler);

	protected:
		void publish(const string& message);

	protected:
		string m_name;
		bool m_started;
		vector<PubSubCb*> m_cb;
	};
}
