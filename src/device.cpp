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

#include <iostream>

#include "device.h"

using namespace std;

HomeHub::Device::Device()
{
  id = 0;
  type = UNKNOWN;
}

HomeHub::Device::Device(const Device& other)
{

}

HomeHub::Device::~Device()
{

}

bool HomeHub::Device::operator==(const Device& other)
{
  return false;
}

void HomeHub::Device::dump()
{
  cout<<"Hello"<<endl;
}
