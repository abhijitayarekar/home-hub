/*
 * pubsub.h
 *
 *  Created on: Jul 8, 2015
 *      Author: abhijit
 */

#ifndef INCLUDE_PUBSUB_H_
#define INCLUDE_PUBSUB_H_

#include "pubsub_common.h"

typedef struct {
	pubsub_impl_t impl;
}pubsub_config_t;

extern pubsub_ret_t pubsub_create(pubsub_config_t* p_config, pubsub_callback_t* p_callbacks);
extern pubsub_ret_t pubsub_start();
extern pubsub_ret_t pubsub_publish(char* channel, json_object *msg);
extern pubsub_ret_t pubsub_stop();
extern pubsub_ret_t pubsub_destroy();

#endif /* INCLUDE_PUBSUB_H_ */
