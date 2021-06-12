#ifndef HARE_SIGNALSAFE_SETJMP_H
#define HARE_SIGNALSAFE_SETJMP_H

#include <setjmp.h>

/***************************************************************
 * hare/signalsafe/setjmp.h async-signal-safe functions of setjmp.h.
 * Only functions of the list in man signal-safety are allowed.
 *
 * @author Hannes Reisinger github@HaRe.at
 ***************************************************************/

namespace hare {
	namespace signalsafe {
		using ::longjmp;
		using ::siglongjmp;
	}	// namespace signalsafe
}	// namespace hare

#endif	// HARE_SIGNALSAFE_SETJMP_H
