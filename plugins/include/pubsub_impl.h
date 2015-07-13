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
	PUBSUB_IMPL_RET_ERR_NO_SUBSCRIBE,
	PUBSUB_IMPL_RET_ERR_NO_SYNC,
}pubsub_impl_ret_t;

typedef struct {
	pubsub_impl_ret_t (*create)(pubsub_callback_t* p_callbacks);
	pubsub_impl_ret_t (*start)();
	pubsub_impl_ret_t (*publish)(char* channel, json_object *msg);
	pubsub_impl_ret_t (*stop)();
	pubsub_impl_ret_t (*destroy)();
} pubsub_impl_ops_t;

#endif /* PLUGINS_INCLUDE_PUBSUB_IMPL_H_ */
