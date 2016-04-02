/*
 ============================================================================
 Name        : controller.cpp
 Author      : Abhijit Ayarekar
 Version     :
 Copyright   : 
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include "controller.h"
#include "worker.h"

using namespace Controller;

int main(void)
{
	Ctrlr ctrl;

	ctrl.start();

	while(1) {
		usleep(1000);
	}
	
	ctrl.stop();

	return EXIT_SUCCESS;
}
