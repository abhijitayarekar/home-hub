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

using namespace Controller;

Ctrlr::Ctrlr() : m_context (1), m_socket (m_context, ZMQ_REP)
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
		m_socket.bind ("tcp://127.0.0.1:5555");
		this->m_started = true;
		m_pubsub.start();
	}

	cout<<"Controller started : "<<this->m_started<<endl;
}

void Ctrlr::stop() 
{
	if(this->m_started) {
		m_pubsub.stop();
		m_socket.unbind("tcp://127.0.0.1:5555");
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
