#ifndef HARE_CTYPE_H
#define HARE_CTYPE_H

#include <ctype.h>

/***************************************************************
 * hare/ctype.h handy convenience methods for ctype.h.
 *
 * @author Hannes Reisinger github@HaRe.at
 ***************************************************************/

namespace hare {
	// skip leading spaces of a zero terminated string of constant chars.
	// @return the new starting position of the string.
	inline const char* skip_space(const char* sz) {
		while (isspace(*sz)
			++sz;
		return sz;
	}

	// skip leading spaces of a zero terminated string of modifyable chars.
	// @return the new starting position of the string.
	inline char* skip_space(char* sz) {
		while (isspace(*sz)
			++sz;
		return sz;
	}
}	// namespace hare

#endif	// HARE_CTYPE_H
