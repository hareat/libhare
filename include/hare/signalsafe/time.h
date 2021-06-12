#ifndef HARE_SIGNALSAFE_TIME_H
#define HARE_SIGNALSAFE_TIME_H

#include <time.h>

/***************************************************************
 * hare/signalsafe/time.h async-signal-safe functions of time.h.
 * Only functions of the list in man signal-safety are allowed.
 *
 * @author Hannes Reisinger github@HaRe.at
 ***************************************************************/

namespace hare {
	namespace signalsafe {
		using ::clock_gettime;
		using ::time;
		using ::timer_getoverrun;
		using ::timer_gettime;
		using ::timer_settime;
	}	// namespace signalsafe
}	// namespace hare

#endif	// HARE_SIGNALSAFE_TIME_H
