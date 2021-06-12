#ifndef HARE_SIGNALSAFE_FCNTL_H
#define HARE_SIGNALSAFE_FCNTL_H

#include <fcntl.h>

/***************************************************************
 * hare/signalsafe/fcntl.h async-signal-safe functions of fcntl.h.
 * Only functions of the list in man signal-safety are allowed.
 *
 * @author Hannes Reisinger github@HaRe.at
 ***************************************************************/

namespace hare {
	namespace signalsafe {
		using ::creat;
		using ::fcntl;
		using ::open;
		using ::openat;
	}	// namespace signalsafe
}	// namespace hare

#endif	// HARE_SIGNALSAFE_FCNTL_H
