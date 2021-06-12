#ifndef HARE_SIGNALSAFE_TIMES_H
#define HARE_SIGNALSAFE_TIMES_H

#include <sys/times.h>

/***************************************************************
 * hare/signalsafe/times.h async-signal-safe functions of times.h.
 * Only functions of the list in man signal-safety are allowed.
 *
 * @author Hannes Reisinger github@HaRe.at
 ***************************************************************/

namespace hare {
	namespace signalsafe {
		using ::times;
	}	// namespace signalsafe
}	// namespace hare

#endif	// HARE_SIGNALSAFE_TIMES_H
