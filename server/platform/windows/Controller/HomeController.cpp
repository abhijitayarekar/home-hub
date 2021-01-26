// Controller.cpp : main project file.

#include <unistd.h>
#include "platdep.h"
#include "controller.h"
#include "pubsub.h"

using namespace Controller;

static bool keepRunning = true;

int main()
{
	Ctrlr* ctrl = Ctrlr::getInstance();

	ctrl->start();

	while (keepRunning) {
		usleep(1000);
	}

	ctrl->stop();

    return 0;
}
