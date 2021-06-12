#ifndef HARE_SIGNALSAFE_SEMAPHORE_H
#define HARE_SIGNALSAFE_SEMAPHORE_H

#include <semaphore.h>

/***************************************************************
 * hare/signalsafe/semaphore.h async-signal-safe functions of semaphore.h.
 * Only functions of the list in man signal-safety are allowed.
 *
 * @author Hannes Reisinger github@HaRe.at
 ***************************************************************/

namespace hare {
	namespace signalsafe {
		using ::sem_post;
	}	// namespace signalsafe
}	// namespace hare

#endif	// HARE_SIGNALSAFE_SEMAPHORE_H
