#ifndef HARE_SIGNALSAFE_AIO_H
#define HARE_SIGNALSAFE_AIO_H

#include <aio.h>

/***************************************************************
 * hare/signalsafe/aio.h async-signal-safe functions of aio.h.
 * Only functions of the list in man signal-safety are allowed.
 *
 * @author Hannes Reisinger github@HaRe.at
 ***************************************************************/

namespace hare {
	namespace signalsafe {
		using ::aio_error;
		using ::aio_return;
		using ::aio_suspend;
	}	// namespace signalsafe
}	// namespace hare

#endif	// HARE_SIGNALSAFE_AIO_H
