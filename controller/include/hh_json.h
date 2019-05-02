#pragma once

#include <vector>
#include <string>
#include <iostream>

using namespace std;

namespace Controller
{
	class HhJson
	{
	public:
		
		HhJson(const string& str) {}
		
		virtual ~HhJson() = 0;

		virtual void fromStr(const string& str) = 0;

		virtual string toStr() = 0;
	};
}
