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

PubSub::PubSub() {
}

PubSub::~PubSub() {
	for(PubSubCb* p_cb : this->m_cb) {
        cout << "Removing pubsub calback handler: "<< p_cb << '\n';
    }

}

void PubSub::start()
{
	if (!this->m_started) {
		cout<<"PubSub starting"<<endl;
		this->m_started = true;
	} 
	cout<<"PubSub started"<<endl;
}

void PubSub::stop() {
	if(this->m_started) {
		this->m_started = false;
		cout<<"PubSub stopped"<<endl;
	}
}

void PubSub::addCb(PubSubCb* p_handler) 
{
	for(PubSubCb* p_cb : this->m_cb) {
		if(p_cb == p_handler) {
			cout<<"Callback already added : "<<p_handler<<endl;
			return;
		}
	}

	m_cb.push_back(p_handler);
	cout << "Adding pubsub calback handler: "<< p_handler << '\n';
}

void PubSub::removeCb(PubSubCb* p_handler)
{
	for(auto it = m_cb.begin(); it != m_cb.end();) {
		if(*it == p_handler) {
			cout<<"Callback removed : "<<p_handler<<endl;
			it = m_cb.erase(it);
			return;
		}
		++it;
	}
}
