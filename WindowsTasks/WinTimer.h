#pragma once

#include <Windows.h>

class WinTimer
{
public:
	WinTimer();

	~WinTimer();

	void Start();

	void End();

	__int64 CalculateTotalTime();

	__int64 CalculateKernalTime();

	__int64 CalculateUserTime();

private:
	FILETIME kernalTimeStart;
	FILETIME kernalTimeEnd;
	FILETIME userTimeStart;
	FILETIME userTimeEnd;
};

