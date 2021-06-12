#ifndef HARE_SIGNALSAFE_STAT_H
#define HARE_SIGNALSAFE_STAT_H

#include <stat.h>

/***************************************************************
 * hare/signalsafe/stat.h async-signal-safe functions of stat.h.
 * Only functions of the list in man signal-safety are allowed.
 *
 * @author Hannes Reisinger github@HaRe.at
 ***************************************************************/

namespace hare {
	namespace signalsafe {
		using ::chmod;
		using ::fchmod;
		using ::fchmodat;
		using ::fstat;
		using ::fstatat;
		using ::futimens;
		using ::lstat;
		using ::mkdir;
		using ::mkdirat;
		using ::mkfifo;
		using ::mkfifoat;
		using ::mknod;
		using ::mknodat;
		using ::stat;
		using ::umask;
		using ::utimensat;
	}	// namespace signalsafe
}	// namespace hare

#endif	// HARE_SIGNALSAFE_STAT_H
