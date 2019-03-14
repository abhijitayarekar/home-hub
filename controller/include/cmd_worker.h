#pragma once
#include "worker.h"

namespace Controller
{
	class CmdWorker : public Worker {
		public:
			CmdWorker(const string& name) : Worker(name) {}

			~CmdWorker() {}

			void doWork() {
				while (m_started) {
					auto t = std::time(nullptr);
					auto tm = *std::localtime(&t);
					cout << m_name << " Sleeping : " << std::put_time(&tm, "%d-%m-%Y %H-%M-%S") << endl;
					std::this_thread::sleep_for(std::chrono::seconds(5));
				}
			}
	};
}

