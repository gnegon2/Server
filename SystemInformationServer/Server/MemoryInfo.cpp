#include "stdafx.h"
#include "MemoryInfo.h"
#include "windows.h"
#include <string>

string MemoryInfo::getInfo()
{
	MEMORYSTATUSEX statex;

	statex.dwLength = sizeof(statex);

	GlobalMemoryStatusEx(&statex);

	string memoryUsageText;
	memoryUsageText = "Memory usage: ";
	memoryUsageText += to_string(statex.dwMemoryLoad);
	memoryUsageText += "%.";

	return memoryUsageText;
}
