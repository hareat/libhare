#ifndef HARE_UNISTD_H
#define HARE_UNISTD_H

#include <unistd.h>

/***************************************************************
 * hare/unistd.h handy convenience methods for unistd.h.
 *
 * @author Hannes Reisinger github@HaRe.at
 ***************************************************************/

namespace hare {
	inline unsigned int sleep_seconds(unsigned int seconds) {
		return ::sleep(seconds);
	}
	inline unsigned int sleep_s(unsigned int seconds) {
		return ::sleep(seconds);
	}
	inline unsigned int sleep_minutes(unsigned int minutes) {
		return ::sleep(minutes * 60U);
	}
	inline unsigned int sleep_m(unsigned int minutes) {
		return ::sleep(minutes * 60U);
	}
	inline unsigned int sleep_hours(unsigned int minutes) {
		return ::sleep(minutes * 3600U);
	}
	inline unsigned int sleep_h(unsigned int minutes) {
		return ::sleep(minutes * 3600U);
	}
	inline unsigned int sleep_days(unsigned int minutes) {
		return ::sleep(minutes * 86400U);
	}
	inline unsigned int sleep_d(unsigned int minutes) {
		return ::sleep(minutes * 86400U);
	}
	inline unsigned int sleep_weeks(unsigned int minutes) {
		return ::sleep(minutes * 604800U);
	}
	inline unsigned int sleep_w(unsigned int minutes) {
		return ::sleep(minutes * 604800U);
	}
}	// namespace hare

#endif	// HARE_UNISTD_H
