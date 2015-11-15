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

#include “homehub.h”
#include “device.h”

namespace HomeHub
{
  class Zone
  {
    private:
    unsigned int id;
    string name;
    std::vector<Device> devices;

  };

  class Scene
  {
    private:
    unsigned int id;
    string name;
    std::vector<Device> devices;

  };
   
  class Home
  {
    private:
    unsigned int id;
    std::vector<Zone> zones;
    std::vector<Zone> scenes;

    public:
    Home();
    Home(const Home& other);
    ~Home();
    bool operator==(const Home& other);
    void dump();
    HomeHub::ret_t start();
    HomeHub::ret_t stop();
    HomeHub::ret_t restart();
  };
};

#endif // HOME_H
