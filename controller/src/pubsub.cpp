/*
 ============================================================================
 Name        : controller.cpp
 Author      : Abhijit Ayarekar
 Version     :
 Copyright   : 
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <iostream>

#include "controller.h"

using namespace Controller;

PubSub::~PubSub() {
	for(PubSubCb* cb : this->m_cb) {
        cout << m_name << " : Removing pubsub calback handler: "<< cb << '\n';
    }

}

void PubSub::start()
{
	if (!this->m_started) {
		cout << m_name << " : Starting"<<endl;
		this->m_started = true;
	}
}

void PubSub::stop() {
	if(this->m_started) {
		cout << m_name << " : Stopping"<<endl;
		this->m_started = false;
	}
}

void PubSub::addCb(PubSubCb* handler) 
{
	for (PubSubCb* cb : this->m_cb) {
		if(cb == handler) {
			cout << m_name << " : Callback already added : "<<handler<<endl;
			return;
		}
	}

	m_cb.push_back(handler);
	cout << m_name << " : Adding calback handler: "<< handler << '\n';
}

void PubSub::removeCb(PubSubCb* handler)
{
	for(auto it = m_cb.begin(); it != m_cb.end();) {
		if(*it == handler) {
			cout << m_name << " : Callback removed : "<<handler<<endl;
			it = m_cb.erase(it);
			return;
		}
		++it;
	}
}

void PubSub::publish(const string& message)
{
	for (PubSubCb* cb : this->m_cb) {
		cb->onMessage(message);
	}

}
