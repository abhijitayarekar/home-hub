/*
 * pubsub.c
 *
 *  Created on: Jul 8, 2015
 *      Author: abhijit
 */

#include "pubsub.h"
#include "pubsub_impl.h"
#include "pubsub_impl_pubnub.h"

static pubsub_impl_ops_t _pubnub_ops;

pubsub_ret_t pubsub_create(pubsub_config_t* p_config, pubsub_callback_t* p_callbacks) {

	pubsub_impl_pubunub_init(&_pubnub_ops);
	if (_pubnub_ops.create) {
		if (_pubnub_ops.create(p_callbacks) == PUBSUB_IMPL_RET_OK) {
			return PUBSUB_RET_OK;
		}
	}
	return PUBSUB_RET_ERR;
}

pubsub_ret_t pubsub_start() {
	if (_pubnub_ops.start) {
		if (_pubnub_ops.start() == PUBSUB_IMPL_RET_OK) {
			return PUBSUB_RET_OK;
		}
	}
	return PUBSUB_RET_ERR;
}

pubsub_ret_t pubsub_publish(char* p_channel, json_object *p_msg) {
	if (_pubnub_ops.publish) {
		if (_pubnub_ops.publish(p_channel, p_msg) == PUBSUB_IMPL_RET_OK) {
			return PUBSUB_RET_OK;
		}
	}
	return PUBSUB_RET_ERR;
}

pubsub_ret_t pubsub_stop() {
	if (_pubnub_ops.stop) {
		if (_pubnub_ops.stop() == PUBSUB_IMPL_RET_OK) {
			return PUBSUB_RET_OK;
		}
	}
	return PUBSUB_RET_ERR;
}

pubsub_ret_t pubsub_destroy() {
	if (_pubnub_ops.destroy) {
		if (_pubnub_ops.destroy() == PUBSUB_IMPL_RET_OK) {
			return PUBSUB_RET_OK;
		}
	}
	return PUBSUB_RET_ERR;
}

