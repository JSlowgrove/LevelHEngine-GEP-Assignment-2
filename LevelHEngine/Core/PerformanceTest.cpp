#include "PerformanceTest.h"

#include "Logging.h"

PerformanceTest::PerformanceTest()
{
}

PerformanceTest::~PerformanceTest()
{
}

void PerformanceTest::testStart()
{
	QueryPerformanceFrequency(&frequency);
	QueryPerformanceCounter(&startingTime);
}

uint64_t PerformanceTest::testFinish()
{
	LARGE_INTEGER endingTime, elapsedMicroseconds;

	QueryPerformanceCounter(&endingTime);
	elapsedMicroseconds.QuadPart = endingTime.QuadPart - startingTime.QuadPart;

	elapsedMicroseconds.QuadPart *= 1000000;
	elapsedMicroseconds.QuadPart /= frequency.QuadPart;

	Logging::logI(std::to_string(elapsedMicroseconds.QuadPart));

	return elapsedMicroseconds.QuadPart;
}