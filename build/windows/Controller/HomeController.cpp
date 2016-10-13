// Controller.cpp : main project file.

#include "stdafx.h"

#include "controller.h"
#include "worker.h"
#include "pubsub.h"

using namespace System;
using namespace Controller;

static bool keepRunning = true;

int main(array<System::String ^> ^args)
{
    Console::WriteLine(L"Hello World");

	Ctrlr ctrl;

	ctrl.start();

	while (keepRunning) {
		_sleep(1000);
	}

	ctrl.stop();

	return EXIT_SUCCESS;

    return 0;
}
