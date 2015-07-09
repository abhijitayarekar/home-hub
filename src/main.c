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


int
main(void)
{
	/* Subscribe */

	do {
		const char *channels[] = { "chat", "demo" };
		pubnub_subscribe_multi(
				/* struct pubnub */ p,
				/* list of channels */ channels,
				/* number of listed channels */ 2,
				/* default timeout */ -1,
				/* callback; sync needs NULL! */ NULL,
				/* callback data */ NULL);
		if (pubnub_sync_last_result(sync) != PNR_OK)
			return EXIT_FAILURE;
		msg = pubnub_sync_last_response(sync);
		if (json_object_array_length(msg) == 0) {
			printf("pubnub subscribe ok, no news\n");
		} else {
			char **msg_channels = pubnub_sync_last_channels(sync);
			for (int i = 0; i < json_object_array_length(msg); i++) {
				json_object *msg1 = json_object_array_get_idx(msg, i);
				printf("pubnub subscribe [%s]: %s\n", msg_channels[i], json_object_get_string(msg1));
			}
		}
		json_object_put(msg);
		sleep(1);
	} while (1);


	pubnub_done(p);
	return EXIT_SUCCESS;
}
