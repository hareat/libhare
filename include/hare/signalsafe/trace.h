#ifndef HARE_SIGNALSAFE_TRACE_H
#define HARE_SIGNALSAFE_TRACE_H

#include <trace.h>

/***************************************************************
 * hare/signalsafe/trace.h async-signal-safe functions of trace.h.
 * Only functions of the list in man signal-safety are allowed.
 *
 * @author Hannes Reisinger github@HaRe.at
 ***************************************************************/

namespace hare {
	namespace signalsafe {
		using ::posix_trace_event;
	}	// namespace signalsafe
}	// namespace hare

#endif	// HARE_SIGNALSAFE_TRACE_H
