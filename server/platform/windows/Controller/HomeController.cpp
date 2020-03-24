// Controller.cpp : main project file.

#include "stdafx.h"

#include "platdep.h"
#include "controller.h"
#include "worker.h"
#include "pubsub.h"

using namespace Controller;

static bool keepRunning = true;

int main()
{
	Ctrlr ctrl;

	ctrl.start();

	while (keepRunning) {
		plat_sleep(1000);
	}

	ctrl.stop();

	return EXIT_SUCCESS;

    return 0;
}
