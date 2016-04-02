#pragma once

#include <iostream>
#include <zmq.hpp>

using namespace std;

namespace Controller
{
	class Ctrlr
	{
	public:
		Ctrlr() : context (1), socket (context, ZMQ_REP){
		}

		~Ctrlr() {
		}

		void start() {
			if (!this->started) {
				cout<<"Controller starting"<<endl;
				socket.bind ("tcp://127.0.0.1:5555");					
				this->started = true;
			} 
			cout<<"Controller started : "<<this->started<<endl;	
		}

		void stop() {
			if(this->started) {
				socket.unbind("tcp://*:5555");
				this->started = false;
				cout<<"Controller stopped"<<endl;
			}
		}
		
	private:
		zmq::context_t context;
		zmq::socket_t socket;
		bool started;
	};
}
