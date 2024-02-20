#pragma once
#include <Windows.h>

class Timer
{
public:
	Timer()
	{
		QueryPerformanceFrequency((LARGE_INTEGER * ) & tick);
	}

	void Start() {
		QueryPerformanceCounter((LARGE_INTEGER *)&start);
	}

	float End() {
		QueryPerformanceCounter((LARGE_INTEGER *)&end);

		return ((double)(end - start) / tick );//ms단위->초로 반환하기
	}

private:
	__int64 tick;
	__int64 start, end;
};