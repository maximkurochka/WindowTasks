#include "WinTimer.h"

static __int64 FileTimeToQuadWord(PFILETIME fileTime)
{
	return(Int64ShllMod32(fileTime->dwHighDateTime, 32) | fileTime->dwLowDateTime);
}

WinTimer::WinTimer()
{
	Start();
}

WinTimer::~WinTimer()
{
}

void WinTimer::Start()
{
	FILETIME tmp;
	GetThreadTimes(
		GetCurrentThread(),
		&tmp,
		&tmp,
		&kernalTimeStart,
		&userTimeStart
	);
}

void WinTimer::End()
{
	FILETIME tmp;
	GetThreadTimes(
		GetCurrentThread(),
		&tmp,
		&tmp,
		&kernalTimeEnd,
		&userTimeEnd
	);
}

__int64 WinTimer::CalculateTotalTime()
{
	return CalculateKernalTime() + CalculateUserTime();
}

__int64 WinTimer::CalculateKernalTime()
{
	return FileTimeToQuadWord(&kernalTimeEnd) - FileTimeToQuadWord(&kernalTimeStart);
}

__int64 WinTimer::CalculateUserTime()
{
	return FileTimeToQuadWord(&userTimeEnd) - FileTimeToQuadWord(&userTimeStart);
}
