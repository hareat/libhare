#ifndef HARE_SIGNALSAFE_POLL_H
#define HARE_SIGNALSAFE_POLL_H

#include <poll.h>

/***************************************************************
 * hare/signalsafe/poll.h async-signal-safe functions of poll.h.
 * Only functions of the list in man signal-safety are allowed.
 *
 * @author Hannes Reisinger github@HaRe.at
 ***************************************************************/

namespace hare {
	namespace signalsafe {
		using ::poll;
	}	// namespace signalsafe
}	// namespace hare

#endif	// HARE_SIGNALSAFE_POLL_H
