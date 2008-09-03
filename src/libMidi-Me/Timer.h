#ifndef MIDIME_TIMER_H
#define MIDIME_TIMER_H

// Includes
#include "global.h"

namespace MidiMe
{
	/** This class is a cross-platform timer.
		You can get the current tick (in miliseconds) and sleep.
	*/
	class LIBMIDIME_API Timer
	{
	public:
		struct LIBMIDIME_API TimeValue
		{
			int year;
			int month;  //! 1-12
			int day;    //! 1-31
			int hour;   //! 0-59
			int minute; //! 0-59
			int second; //! 0-59
			int millisecond; //! 0-99

			TimeValue operator-(const TimeValue &time) const;
			string dateString() const;
			string timeString() const;
		};

	public:
		// Static functions
		static unsigned int getTickCount();
		static TimeValue getLocalTime();
		static void wait(unsigned int milliSeconds);
	};
}

#endif // MIDIME_TIMER_H
