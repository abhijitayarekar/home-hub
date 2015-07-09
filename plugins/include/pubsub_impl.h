/*
 * pubsub_impl.h
 *
 *  Created on: Jul 8, 2015
 *      Author: abhijit
 */

#ifndef PLUGINS_INCLUDE_PUBSUB_IMPL_H_
#define PLUGINS_INCLUDE_PUBSUB_IMPL_H_

#include "pubsub_common.h"

typedef enum {
	PUBSUB_IMPL_RET_OK,
	PUBSUB_IMPL_RET_ERR_NO_HANDLE,
	PUBSUB_IMPL_RET_ERR_INVALID_ARG,
	PUBSUB_IMPL_RET_ERR_NO_SYNC,
}pubsub_impl_ret_t;

typedef struct {
	void (*on_publish)(char* channel, json_object *msg);
	void (*on_message)(char* channel, json_object *msg);
}pubsub_impl_callback_t;

extern pubsub_impl_ret_t pubsub_impl_create(pubsub_impl_callback_t* p_callbacks);
extern pubsub_impl_ret_t pubsub_impl_configure();
extern pubsub_impl_ret_t pubsub_impl_start();
extern pubsub_impl_ret_t pubsub_impl_publish(char* channel, json_object *msg);
extern pubsub_impl_ret_t pubsub_impl_stop();
extern pubsub_impl_ret_t pubsub_impl_destroy();

#endif /* PLUGINS_INCLUDE_PUBSUB_IMPL_H_ */
