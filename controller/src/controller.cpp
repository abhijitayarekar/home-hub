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
#include <chrono>
#include <iomanip>

#include "controller.h"
#include "pubsub.h"

#define _IPC_PATH "ipc:///tmp/hh_local_work_0"

using namespace Controller;

Ctrlr::Ctrlr() : m_context (1), m_localConnSocket(m_context, ZMQ_DEALER)
{
	m_pubsub.addCb(this);
}

Ctrlr::~Ctrlr() 
{
	stop();
	m_pubsub.removeCb(this);
}

void Ctrlr::start() 
{
	if (!this->m_started) {
		cout<<"Controller starting"<<endl;
		this->m_started = true;
		m_localConnThread = std::thread(&Ctrlr::localConnThreadFunc, this);
		m_pubsub.start();
	}

	cout<<"Controller started"<<endl;
}

void Ctrlr::stop() 
{
	if(this->m_started) {
		this->m_started = false;
		m_pubsub.stop();
		m_localConnThread.join();
		cout<<"Controller stopped"<<endl;
	}
}

void Ctrlr::onMessage(void* p_msg)
{

}

void Ctrlr::localConnThreadFunc()
{
	cout<<endl<<"Local conn thread starting"<<endl;
	m_localConnSocket.bind (_IPC_PATH);
	while (m_started) {
		auto t = std::time(nullptr);
		auto tm = *std::localtime(&t);
		cout<<"Sleeping : "<<std::put_time(&tm, "%d-%m-%Y %H-%M-%S")<<endl;
		std::this_thread::sleep_for(std::chrono::seconds(1));
	}
	m_localConnSocket.unbind(_IPC_PATH);
	cout<<"Local conn thread returning"<<endl;
}
