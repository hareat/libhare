#ifndef HARE_SIGNALSAFE_STRINGS_H
#define HARE_SIGNALSAFE_STRINGS_H

#include <strings.h>

/***************************************************************
 * hare/signalsafe/strings.h async-signal-safe functions of strings.h.
 * Only functions of the list in man signal-safety are allowed.
 *
 * @author Hannes Reisinger github@HaRe.at
 ***************************************************************/

namespace hare {
	namespace signalsafe {
		using ::ffs;
	}	// namespace signalsafe
}	// namespace hare

#endif	// HARE_SIGNALSAFE_STRINGS_H
