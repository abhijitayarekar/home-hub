/*
 ============================================================================
 Name        : worker.cpp
 Author      : Abhijit Ayarekar
 Version     :
 Copyright   : 
 Description : Worker class handles protocol specific work over socket
 ============================================================================
 */

#include <iostream>

#include "zhelpers.hpp"
#include "controller.h"
#include "worker.h"
#include "pubsub.h"

using namespace Controller;

void Worker::work()
{
	m_worker.connect("inproc://local_work");

	try {
	    while (true) {
	        zmq::message_t identity;
	        zmq::message_t msg;
	        zmq::message_t copied_id;
	        zmq::message_t copied_msg;
	        m_worker.recv(&identity);
	        m_worker.recv(&msg);

	        int replies = within(5);
	        for (int reply = 0; reply < replies; ++reply) {
	            s_sleep(within(1000) + 1);
	            copied_id.copy(&identity);
	            copied_msg.copy(&msg);
	            m_worker.send(copied_id, ZMQ_SNDMORE);
	            m_worker.send(copied_msg);
	        }
	    }
	}
	catch (std::exception &e) 
	{
		cout << e.what();
	}
}

# if 0
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
#endif
