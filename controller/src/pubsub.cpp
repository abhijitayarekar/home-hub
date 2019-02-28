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
	for(PubSubCb* p_cb : this->m_cb) {
        cout << m_name << " : Removing pubsub calback handler: "<< p_cb << '\n';
    }

}

void PubSub::start()
{
	if (!this->m_started) {
		cout << m_name << " : Starting"<<endl;
		this->m_started = true;
		cout << m_name << " : started"<<endl;
	}
}

void PubSub::stop() {
	if(this->m_started) {
		cout << m_name << " : Stopping"<<endl;
		this->m_started = false;
		cout << m_name << " : Stopped"<<endl;
	}
}

void PubSub::addCb(PubSubCb* p_handler) 
{
	for(PubSubCb* p_cb : this->m_cb) {
		if(p_cb == p_handler) {
			cout << m_name << " : Callback already added : "<<p_handler<<endl;
			return;
		}
	}

	m_cb.push_back(p_handler);
	cout << m_name << " : Adding calback handler: "<< p_handler << '\n';
}

void PubSub::removeCb(PubSubCb* p_handler)
{
	for(auto it = m_cb.begin(); it != m_cb.end();) {
		if(*it == p_handler) {
			cout << m_name << " : Callback removed : "<<p_handler<<endl;
			it = m_cb.erase(it);
			return;
		}
		++it;
	}
}
