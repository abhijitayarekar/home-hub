/*
 ============================================================================
 Name        : controller.cpp
 Author      : Abhijit Ayarekar
 Version     :
 Copyright   : 
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include "platdep.h"
#include <iostream>

#include "controller.h"
#include "worker.h"
#include "pubsub.h"

#define _IPC_PATH "ipc:///tmp/hh_local_work_0"

using namespace Controller;

Ctrlr::Ctrlr() : m_context (1), m_localWorkerSocket(m_context, ZMQ_DEALER)
{
	m_pubsub.addCb(this);
}

Ctrlr::~Ctrlr() 
{
}

void Ctrlr::start() 
{
	if (!this->m_started) {
		cout<<"Controller starting"<<endl;
		m_localWorkerSocket.bind (_IPC_PATH);
		this->m_started = true;
		m_pubsub.start();
	}

	cout<<"Controller started : "<<this->m_started<<endl;
}

void Ctrlr::stop() 
{
	if(this->m_started) {
		m_pubsub.stop();
		m_localWorkerSocket.unbind(_IPC_PATH);
		this->m_started = false;
		cout<<"Controller stopped"<<endl;
	}
}

void Ctrlr::onMessage(void* p_msg)
{

}

