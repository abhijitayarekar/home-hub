#pragma once
#include "worker.h"

namespace Controller
{
	class CmdWorker : public Worker {
		public:
			CmdWorker(const string& name) : Worker(name) {}

			~CmdWorker() {}

			void doWork();
	};
}

