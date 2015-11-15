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

#ifndef DEVICE_H
#define DEVICE_H

#include "homehub.h"

namespace HomeHub
{
  class Device
  {
    public:
    enum dev_type
    {
    	UNKNOWN, IP, ZIGBEE, BT, ZWAVE
    };

    enum dev_state
    {
    	OFF, STARTING, ON, STOPPING
    };

    private:
    unsigned int id;
    dev_type type;
    dev_state state;

    public:
    Device();
    Device(const Device& other);
    ~Device();
    bool operator==(const Device& other);
    void dump();
    HomeHub::ret_t start();
    HomeHub::ret_t stop();
    HomeHub::ret_t restart();
  };
}

#endif // DEVICE_H
