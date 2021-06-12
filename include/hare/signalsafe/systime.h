#ifndef HARE_SIGNALSAFE_SYSTIME_H
#define HARE_SIGNALSAFE_SYSTIME_H

#include <sys/time.h>

/***************************************************************
 * hare/signalsafe/systime.h async-signal-safe functions of sys/time.h.
 * Only functions of the list in man signal-safety are allowed.
 *
 * @author Hannes Reisinger github@HaRe.at
 ***************************************************************/

namespace hare {
	namespace signalsafe {
		using ::utimes;
	}	// namespace signalsafe
}	// namespace hare

#endif	// HARE_SIGNALSAFE_SYSTIME_H
