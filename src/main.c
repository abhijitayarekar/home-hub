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

#include "pubsub.h"

static void _on_publish(char* channel, json_object *msg) {

}

static void _on_message(char* channel, json_object *msg) {

}

static pubsub_callback_t _pubsub_callbacks = {
		_on_publish,
		_on_message
};

static pubsub_config_t _pubsub_config;

int
main(void)
{
	_pubsub_config.impl = PUBSUB_IMPL_PUBNUB;

	printf( "TRACE 1\n");
	pubsub_create(&_pubsub_config, &_pubsub_callbacks);
	pubsub_start();
	pubsub_destroy();
	printf("TRACE 2 \n");
	return EXIT_SUCCESS;
}
