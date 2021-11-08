#ifndef HARE_THROWS_ICONV_H
#define HARE_THROWS_ICONV_H

#include <iconv.h>

/***************************************************************************
 * Throws an exception (derived of std::system_error) in case of any error.
 *
 * @author Hannes Reisinger github@HaRe.at
 ***************************************************************************/

#include <hare/stdexcept>	// CHECK_NOT_NULL_ARG
#include <hare/system_error>

namespace hare {
	namespace throws {
		inline iconv_t iconv_open(const char *tocode, const char *fromcode) {
			CHECK_NOT_NULL_ARG2(tocode, fromcode);
			const iconv_t cd = ::iconv_open(tocode, fromcode);
			if (cd == ((iconv_t) -1))
				throw hare::system_error("%s(\"%s\", \"%s\") failed", __func__, tocode, fromcode);
			return cd;
		}

		inline size_t iconv(iconv_t cd, char **inbuf, size_t *inbytesleft, char **outbuf, size_t *outbytesleft) {
			const size_t result = ::iconv(cd, inbuf, inbytesleft, outbuf, outbytesleft);
			if (result == ((size_t) -1))
				throw hare::system_error("%s() failed", __func__);
			return result;
		}

		inline void iconv_close(iconv_t cd) {
			if (::iconv_close(cd) == -1)
				throw hare::system_error("%s() failed", __func__);
		}
	}	// namespace throws
}	// namespace hare

#endif	// HARE_THROWS_ICONV_H
