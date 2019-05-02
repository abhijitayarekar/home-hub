/*
 * Copyright 2015 <copyright holder> <email>
 * 
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 * 
 *     http://www.apache.org/licenses/LICENSE-2.0
 * 
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 * 
 */

#ifndef HOMEHUB_H
#define HOMEHUB_H

#include <iostream>
#include <string>

using namespace std;

namespace HomeHub
{
	enum ret_t
	{
		no_error
	};

	enum HH_MSG_TYPE_E {
		MSG_MIN,
		EVENT,
		COMMAND,
		MSG_MAX
	};

	const static string HH_MSG_TYPE_STR[] = {
		"-invalid",
		"evnt",
		"cmd",
		"invalid"
	};
#if 0
	static const string& getMsgTypeStr(HH_MSG_TYPE_E e_type) {
		if (e_type <= MSG_MIN || e_type >= MSG_MAX)
			return HH_MSG_TYPE_STR[MSG_MAX];

		return HH_MSG_TYPE_STR[e_type];
	}

	static const HH_MSG_TYPE_E getMsgType(const string& msg_str) {
		for (int i = MSG_MIN; i < MSG_MAX; i++) {
			if (msg_str == HH_MSG_TYPE_STR[i])
				return (HH_MSG_TYPE_E)i;
		}
		return MSG_MIN;
	}
#endif
}

#endif // HOMEHUB_H
