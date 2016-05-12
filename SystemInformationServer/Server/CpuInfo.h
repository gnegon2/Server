#pragma once

#include "Info.h"
#include <string>

using namespace std;

class CpuInfo :
	public Info
{
public:
	CpuInfo();
	virtual string getInfo();
	virtual ~CpuInfo();
};

