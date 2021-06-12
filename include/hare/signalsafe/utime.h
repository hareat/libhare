#ifndef HARE_SIGNALSAFE_UTIME_H
#define HARE_SIGNALSAFE_UTIME_H

#include <utime.h>

/***************************************************************
 * hare/signalsafe/utime.h async-signal-safe functions of utime.h.
 * Only functions of the list in man signal-safety are allowed.
 *
 * @author Hannes Reisinger github@HaRe.at
 ***************************************************************/

namespace hare {
	namespace signalsafe {
		using ::utime;
	}	// namespace signalsafe
}	// namespace hare

#endif	// HARE_SIGNALSAFE_UTIME_H
