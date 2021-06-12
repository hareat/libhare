#ifndef HARE_SIGNALSAFE_WAIT_H
#define HARE_SIGNALSAFE_WAIT_H

#include <sys/wait.h>

/***************************************************************
 * hare/signalsafe/wait.h async-signal-safe functions of wait.h.
 * Only functions of the list in man signal-safety are allowed.
 *
 * @author Hannes Reisinger github@HaRe.at
 ***************************************************************/

namespace hare {
	namespace signalsafe {
		using ::wait;
		using ::waitpid;
	}	// namespace signalsafe
}	// namespace hare

#endif	// HARE_SIGNALSAFE_WAIT_H
