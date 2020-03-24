#include "pubsub.h"

using namespace std;
using namespace Controller;

PubSub::PubSub(const string& name) : m_name(name)
{
}

PubSub::~PubSub()
{
	for(PubSubCb* cb : this->m_cb)
		cout << m_name << " : Removing pubsub calback handler: "<< cb << endl;
}

void PubSub::start()
{
	if (!this->m_started) {
		cout << m_name << " : Starting"<<endl;
		this->m_started = true;
	}
}

void PubSub::stop()
{
	if(this->m_started) {
		cout << m_name << " : Stopping"<<endl;
		this->m_started = false;
	}
}

void PubSub::addCb(PubSubCb* handler)
{
	for (PubSubCb* cb : this->m_cb) {
		if(cb == handler) {
			cout << m_name << " : Callback already added : " << handler << endl;
			return;
		}
	}

	m_cb.push_back(handler);
	cout << m_name << " : Adding callback handler: " << handler << endl;
}

void PubSub::removeCb(PubSubCb* handler)
{
	for(auto it = m_cb.begin(); it != m_cb.end();) {
		if(*it == handler) {
			cout << m_name << " : Callback removed : " << handler << endl;
			it = m_cb.erase(it);
			return;
		}
		++it;
	}

}

void PubSub::publish(const string& message)
{
	for(PubSubCb* cb : this->m_cb)
		cb->onMessage(message);
}
