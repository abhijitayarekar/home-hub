#pragma once

#include <string>
#include <iostream>
#include <vector>

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
		PubSub(const string& name);

		~PubSub();

		void start();

		void stop();

		void addCb(PubSubCb* handler);

		void removeCb(PubSubCb* handler);

	protected:
		void publish(const string& message);

	protected:
		string m_name;
		bool m_started;
		vector<PubSubCb*> m_cb;
	};
}
