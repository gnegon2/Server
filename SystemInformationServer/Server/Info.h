#pragma once

#include <string>

using namespace std;

class Info
{
public:
	virtual string getInfo() = 0;
	virtual ~Info();
};

