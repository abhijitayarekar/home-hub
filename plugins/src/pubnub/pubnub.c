/*
 * pubnub.c
 *
 *  Created on: Jul 8, 2015
 *      Author: abhijit
 */
#include <stdio.h>
#include <unistd.h>

#include "pubnub.h"
#include "pubnub-sync.h"

#include "pubsub_impl.h"

static struct pubnub *_p_pubnub = NULL;
static struct pubnub_sync *_p_sync = NULL;
static pubsub_callback_t* _p_callbacks = NULL;

static pubsub_impl_ret_t _pubnub_create(pubsub_callback_t* p_callbacks) {

	_p_callbacks = p_callbacks;
	_p_sync = pubnub_sync_init();
	_p_pubnub = pubnub_init(
			/* publish_key */ "pub-c-0d1e3317-dac1-4508-8def-f750890c1259",
			/* subscribe_key */ "sub-c-37743c0c-1add-11e5-bbfe-0619f8945a4f",
			/* pubnub_callbacks */ &pubnub_sync_callbacks,
			/* pubnub_callbacks data */ _p_sync);

	return PUBSUB_IMPL_RET_OK;
}

static pubsub_impl_ret_t _pubnub_start() {

	struct json_object *p_msgs;
	struct json_object *p_msg;
	int i;
	char **pp_msg_channels;
	const char *channels[] = { "chat", "demo" };

	if (!_p_pubnub || _p_sync) {
		return PUBSUB_IMPL_RET_ERR_NO_HANDLE;
	}

	do {

		pubnub_subscribe_multi(
				/* struct pubnub */ _p_pubnub,
				/* list of channels */ channels,
				/* number of listed channels */ 2,
				/* default timeout */ -1,
				/* callback; sync needs NULL! */ NULL,
				/* callback data */ NULL);
		if (pubnub_sync_last_result(_p_sync) != PNR_OK)
			return PUBSUB_IMPL_RET_ERR_NO_SUBSCRIBE;

		p_msgs = pubnub_sync_last_response(_p_sync);
		if (json_object_array_length(p_msgs) == 0) {
			printf("pubnub subscribe ok, no news\n");
		} else {
			pp_msg_channels = pubnub_sync_last_channels(_p_sync);
			for (i = 0; i < json_object_array_length(p_msgs); i++) {
				p_msg = json_object_array_get_idx(p_msgs, i);
				printf("pubnub subscribe [%s]: %s\n", pp_msg_channels[i], json_object_get_string(p_msg));
			}
		}
		json_object_put(p_msgs);
		sleep(1);
	} while (1);


	pubnub_done(_p_pubnub);

	return PUBSUB_IMPL_RET_OK;
}

static pubsub_impl_ret_t _pubnub_publish(char* channel, json_object *msg) {

	if (!_p_pubnub) {
		return PUBSUB_IMPL_RET_ERR_NO_HANDLE;
	}
	if (!channel || !msg) {
		return PUBSUB_IMPL_RET_ERR_INVALID_ARG;
	}
/*
	msg = json_object_new_object();
	json_object_object_add(msg, "nodeId", json_object_new_string("42"));
	json_object_object_add(msg, "msg", json_object_new_string("\"Hello, world!\""));
*/
	pubnub_publish(
			/* struct pubnub */ _p_pubnub,
			/* channel */ channel,
			/* message */ msg,
			/* default timeout */ -1,
			/* callback; sync needs NULL! */ NULL,
			/* callback data */ NULL);

	json_object_put(msg);

	if (pubnub_sync_last_result(_p_sync) != PNR_OK) {
		return PUBSUB_IMPL_RET_ERR_NO_SYNC;
	}

#if 0
	msg = pubnub_sync_last_response(sync);
	printf("pubnub publish ok: %s\n", json_object_get_string(msg));
	json_object_put(msg);
#endif

	return PUBSUB_IMPL_RET_OK;
}

static pubsub_impl_ret_t _pubnub_stop() {
	return PUBSUB_IMPL_RET_OK;
}

static pubsub_impl_ret_t _pubnub_destroy() {
	return PUBSUB_IMPL_RET_OK;
}

pubsub_impl_ret_t pubsub_impl_pubunub_init(pubsub_impl_ops_t* p_ops) {

	if (!p_ops) {
		return PUBSUB_IMPL_RET_ERR_INVALID_ARG;
	}
	p_ops->create = _pubnub_create;
	p_ops->start = _pubnub_start;
	p_ops->publish = _pubnub_publish;
	p_ops->stop = _pubnub_stop;
	p_ops->destroy = _pubnub_destroy;

	return PUBSUB_IMPL_RET_OK;
}

