#pragma once

#include <iostream>

using namespace std;

namespace Controller
{
	class Ctrlr
	{
	public:
		Ctrlr() {
		}

		~Ctrlr() {
		}

		void start() {
			if (!this->started) {
				cout<<"Controller starting"<<endl;	
				this->started = true;
			} 
			cout<<"Controller started : "<<this->started<<endl;	
		}

		void stop() {
			if(this->started) {
				this->started = false;
				cout<<"Controller stopped"<<endl;
			}
		}
		
	private:
		bool started;
	};
}
