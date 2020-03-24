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

#ifndef HOME_H
#define HOME_H

#include "homehub.h"
#include "device.h"

#include <iostream>
#include <vector>

using namespace std;

namespace HomeHub
{
  class Zone
  {
    private:
    unsigned int id;
    string name;
    std::vector<Device>devices;
    public:
    Zone() {
    	id = 0;
    }
  };

  class Scene
  {
    private:
    unsigned int id;
    string name;
    std::vector<Device> devices;

    public:
    Scene() {
    	id = 0;
    }
  };
   
  class Home
  {
    private:
    unsigned int id;
    std::vector<Zone> zones;
    std::vector<Zone> scenes;

    public:

    Home() {
    	id = 0;
    }

    Home(const Home& other) {
    	id = other.id;
    }

    ~Home() {

    }

    bool operator==(const Home& other) {
    	return id == other.id;
    }

    void dump() {
    	cout<<"Home id:"<<id<<endl;
    }

    HomeHub::ret_t start() {
    	return no_error;
    }

    HomeHub::ret_t stop() {
    	return no_error;
    }

    HomeHub::ret_t restart() {
    	return no_error;
    }
  };
}

#endif // HOME_H
