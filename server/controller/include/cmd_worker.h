#pragma once
#include "worker.h"

namespace Controller
{
	class CmdWorker : public Worker {
		public:
			CmdWorker(const string& name);
			~CmdWorker();
			void doWork();
	};
}

