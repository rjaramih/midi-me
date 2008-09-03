// Includes
#include "Timer.h"
using namespace MidiMe;

#ifndef WIN32 // Only in linux
	#include <sys/time.h>
	#include <unistd.h>
#endif // WIN32


/*******************
* Static functions *
*******************/

unsigned int Timer::getTickCount()
{
#ifdef WIN32 // Only in windows
	return GetTickCount();
#else // Linux
  struct timeval currentTime;
  gettimeofday(&currentTime, 0);
  return currentTime.tv_sec * 1000 + currentTime.tv_usec / 1000;
#endif // WIN32
}

Timer::TimeValue Timer::getLocalTime()
{
	TimeValue timev;

#ifdef WIN32 // Windows
	SYSTEMTIME currentTime;

	GetLocalTime(&currentTime);

	timev.year = currentTime.wYear;
	timev.month = currentTime.wMonth;
	timev.day = currentTime.wDay;
	timev.hour = currentTime.wHour;
	timev.minute = currentTime.wMinute;
	timev.second = currentTime.wSecond;
	timev.millisecond = currentTime.wMilliseconds;

#else // Linux
	struct timeval rawTime;
	struct tm *currentTime;

	gettimeofday(&rawTime, 0);
	currentTime = localtime(&(rawTime.tv_sec));

	timev.year = currentTime->tm_year + 1900;
	timev.month = currentTime->tm_mon + 1;
	timev.day = currentTime->tm_mday;
	timev.hour = currentTime->tm_hour;
	timev.minute = currentTime->tm_min;
	timev.second = currentTime->tm_sec;
	timev.millisecond = rawTime.tv_usec / 1000;
#endif // WIN32

	return timev;
}

void Timer::wait(unsigned int milliSeconds)
{
#ifdef WIN32 // Only in windows
	Sleep(milliSeconds);
#else // Linux
	usleep(milliSeconds * 1000);
#endif // WIN32
}


Timer::TimeValue Timer::TimeValue::operator-(const TimeValue &time) const
{
	TimeValue result;
	result.year = year - time.year;
	result.month = month - time.month;
	result.day = day - time.day;
	result.hour = hour - time.hour;
	result.minute = minute - time.minute;
	result.second = second - time.second;
	result.millisecond = millisecond - time.millisecond;
	return result;
}

string toString(int number)
{
	char buffer[256];
	sprintf(buffer, "%d", number);
	return string(buffer);
}

string Timer::TimeValue::dateString() const
{
	return toString(year) + "-" + toString(month) + "-" + toString(day);
}

string Timer::TimeValue::timeString() const
{
	return toString(hour) + ":" + toString(minute) + ":"
		+ toString(second) + "." + toString(millisecond);
}
