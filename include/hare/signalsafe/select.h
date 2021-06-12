#ifndef HARE_SIGNALSAFE_SELECT_H
#define HARE_SIGNALSAFE_SELECT_H

#include <sys/select.h>

/***************************************************************
 * hare/signalsafe/select.h async-signal-safe functions of select.h.
 * Only functions of the list in man signal-safety are allowed.
 *
 * @author Hannes Reisinger github@HaRe.at
 ***************************************************************/

namespace hare {
	namespace signalsafe {
		using ::pselect;
		using ::select;
	}	// namespace signalsafe
}	// namespace hare

#endif	// HARE_SIGNALSAFE_SELECT_H
