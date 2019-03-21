#pragma once

#include <vector>
#include <string>
#include <iostream>

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
		PubSub(const string& name) : m_name(name) {}
		
		~PubSub() {
			for(PubSubCb* cb : this->m_cb)
				cout << m_name << " : Removing pubsub calback handler: "<< cb << endl;
		}

		void start() {
			if (!this->m_started) {
				cout << m_name << " : Starting"<<endl;
				this->m_started = true;
			}
		}

		void stop() {
			if(this->m_started) {
				cout << m_name << " : Stopping"<<endl;
				this->m_started = false;
			}
		}

		void addCb(PubSubCb* handler) {
			for (PubSubCb* cb : this->m_cb) {
				if(cb == handler) {
					cout << m_name << " : Callback already added : " << handler << endl;
					return;
				}
			}

			m_cb.push_back(handler);
			cout << m_name << " : Adding callback handler: " << handler << endl;
		}

		void removeCb(PubSubCb* handler) {
			for(auto it = m_cb.begin(); it != m_cb.end();) {
				if(*it == handler) {
					cout << m_name << " : Callback removed : " << handler << endl;
					it = m_cb.erase(it);
					return;
				}
				++it;
			}

		}

	protected:
		void publish(const string& message) {
			for(PubSubCb* cb : this->m_cb)
				cb->onMessage(message);

		}

	protected:
		string m_name;
		bool m_started;
		vector<PubSubCb*> m_cb;
	};
}
