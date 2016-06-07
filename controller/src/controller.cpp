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
#include <unistd.h>
#include <signal.h>

#include "controller.h"
#include "worker.h"
#include "pubsub.h"

#define _IPC_PATH "ipc:///tmp/hh_local_work_0"

using namespace Controller;

Ctrlr::Ctrlr() : m_context (1), m_localWorkSocket (m_context, ZMQ_DEALER)
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
		m_localWorkSocket.bind (_IPC_PATH);
		this->m_started = true;
		m_pubsub.start();
	}

	cout<<"Controller started : "<<this->m_started<<endl;
}

void Ctrlr::stop() 
{
	if(this->m_started) {
		m_pubsub.stop();
		m_localWorkSocket.unbind(_IPC_PATH);
		this->m_started = false;
		cout<<"Controller stopped"<<endl;
	}
}

void Ctrlr::onMessage(void* p_msg)
{

}

static bool keepRunning = true;
static void sig_handler(int signo)
{
	if(signo == SIGINT) {
		keepRunning = false;
	}
}

int main(void)
{
	Ctrlr ctrl;

	signal(SIGINT, sig_handler);

	ctrl.start();

	while(keepRunning) {
		usleep(1000);
	}
	
	ctrl.stop();

	return EXIT_SUCCESS;
}
