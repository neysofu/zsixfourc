/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "time/time_control.h"
#include "UGEI/property_names.h"
#include "cJSON/cJSON.h"
#include "utils.h"
#include <assert.h>
#include <stdlib.h>
#include <sys/time.h>

struct TimeControl *
time_control_new_blitz(void)
{
	struct TimeControl *tc = malloc_or_exit(sizeof(struct TimeControl));
	*tc = (struct TimeControl){
		.time_limit = 3 * 60, .increment = 2,
	};
	return tc;
}

struct TimeControl *
time_control_new_rapid(void)
{
	struct TimeControl *tc = malloc_or_exit(sizeof(struct TimeControl));
	*tc = (struct TimeControl){
		.time_limit = 15 * 60, .increment = 10,
	};
	return tc;
}

struct TimeControl *
time_control_new_classical(void)
{
	struct TimeControl *tc0 = malloc_or_exit(sizeof(struct TimeControl));
	struct TimeControl *tc1 = malloc_or_exit(sizeof(struct TimeControl));
	*tc0 = (struct TimeControl){
		.time_limit = 90 * 60,
		.increment = 30,
		.max_trigger_count = 40,
		.next_time_control = tc1,
	};
	*tc1 = (struct TimeControl){
		.time_limit = 30 * 60, .increment = 30, .previous_time_control = tc0,
	};
	return tc0;
}

struct TimeControl *
time_control_new_from_json(struct cJSON *json)
{
	struct TimeControl *time_control = malloc_or_exit(sizeof(struct TimeControl));
	*time_control = (struct TimeControl){ 0 };
	struct cJSON *time_limit = cJSON_GetObjectItem(json, PROPERTY_NAME_TIME_LIMIT);
	struct cJSON *increment = cJSON_GetObjectItem(json, PROPERTY_NAME_INCREMENT);
	struct cJSON *delay = cJSON_GetObjectItem(json, PROPERTY_NAME_DELAY);
	if (time_limit) {
		time_control->time_limit = time_limit->valuedouble;
	}
	if (increment) {
		time_control->increment = time_limit->valuedouble;
	}
	if (delay) {
		time_control->delay = time_limit->valuedouble;
	}
	return time_control;
}

void
time_control_delete(struct TimeControl *tc)
{
	assert(tc);
	while (tc->previous_time_control) {
		tc = tc->previous_time_control;
	}
	while (tc->next_time_control) {
		tc = tc->next_time_control;
		free(tc->previous_time_control);
	}
	free(tc);
}
