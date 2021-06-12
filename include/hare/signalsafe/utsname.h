#ifndef HARE_SIGNALSAFE_UTSNAME_H
#define HARE_SIGNALSAFE_STRINGS_H

#include <sys/utsname.h>

/***************************************************************
 * hare/signalsafe/utsname.h async-signal-safe functions of utsname.h.
 * Only functions of the list in man signal-safety are allowed.
 *
 * @author Hannes Reisinger github@HaRe.at
 ***************************************************************/

namespace hare {
	namespace signalsafe {
		using ::uname;
	}	// namespace signalsafe
}	// namespace hare

#endif	// HARE_SIGNALSAFE_STRINGS_H
