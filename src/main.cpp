/*
 ============================================================================
 Name        : home-controller.c
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

#include "home.h"

using namespace HomeHub;

int
main(void)
{
    Home h;
    h.dump();

	return EXIT_SUCCESS;
}
