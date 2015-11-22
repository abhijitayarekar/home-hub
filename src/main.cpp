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

//#include "pubsub.h"
#include "home.h"
#include "device.h"

using namespace HomeHub;

#if 0
static void _on_publish(char* channel, json_object *msg) {

}

static void _on_message(char* channel, json_object *msg) {

}

static pubsub_callback_t _pubsub_callbacks = {
		_on_publish,
		_on_message
};

static pubsub_config_t _pubsub_config;
#endif

int
main(void)
{
#if 0  
	_pubsub_config.impl = PUBSUB_IMPL_PUBNUB;

	printf( "TRACE 1\n");
	pubsub_create(&_pubsub_config, &_pubsub_callbacks);
	pubsub_start();
	pubsub_destroy();
	printf("TRACE 2 \n");
#endif
    Home h;
    h.dump();

    Device dev_local;
    dev_local.dump();
	
	Bt bt_local;
	bt_local.dump();
	
	XBee xbee_local;
	xbee_local.dump();

    Device dev_remote(HomeHub::Device::UNKNOWN, HomeHub::Device::REMOTE);
    dev_remote.dump();
	
	Bt bt_remote(HomeHub::Bt::REMOTE);
	bt_remote.dump();
	
	XBee xbee_remote(HomeHub::XBee::REMOTE);
	xbee_remote.dump();

	return EXIT_SUCCESS;
}
