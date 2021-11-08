#ifndef HARE_WRAP_ICONV_H
#define HARE_WRAP_ICONV_H

#include <iconv.h>

/***************************************************************************
 * hare/warp/iconv.h some wrappers for iconv.h.
 *
 * Encapsulates a conversion descriptor to ensure iconv_close() is called
 * also in case of an exception.
 *
 * @usage
 * 	const hare::wrap::iconv_t cd(iconv_open(to, from));
 *	if (!cd)
 *		exit(EXIT_FAILURE);
 *	else {
 *		iconv(cd, ...);
 *		...
 *	<automatically close the cd also in case of an exception>
 * or simpler
 * 	const hare::wrap::iconv_t cd(hare::throws::iconv_open(to, from));
 *	hare::throws::iconv(cd, ...);
 *	...
 *	<automatically close the cd also in case of an exception>
 *
 * @author Hannes Reisinger github@HaRe.at
 **************************************************************************/

#include <hare/system_error>

namespace hare {
	namespace wrap {
		struct iconv_t {
			::iconv_t m_cd;	// the encapsulated conversion descriptor
		public:
			iconv_t() : m_cd(-1) {}
			iconv_t(::iconv_t cd) : m_cd(cd) {}

			~iconv_t() { if (m_cd != -1) ::iconv_close(m_cd); }

			iconv_t& operator=(::iconv_t cd) {
				if (m_cd)
					::iconv_close(m_cd);
				m_cd = cd;
				return *this;
			}

			// use std::shared_ptr instead
			iconv_t(const iconv_t&) = delete;
			iconv_t& operator=(const iconv_t&) = delete;

			// returns zero on success.
			// On error, -1 is returned, and errno is set appropriately.
			int iconv_close() {
				if (m_cd != -1) {
					const int result = ::iconv_close(m_cd);
					m_cd = -1;
					return result;
				}
				else
					return 0;
			}

			// to use it like a file descriptor
			operator ::iconv_t() const { return m_cd; }
		};
	}	// namespace wrap

	namespace throws {
		inline void iconv_close(hare::wrap::iconv_t &cd) {
			if (cd.iconv_close() == -1)
				throw hare::system_error("%s() failed", __func__);
		}
	}	// namespace throws
}	// namespace hare


// to avoid accidentally calls
int iconv_lose(hare::wrap::FD &fd) { return fd.iconv_close(); }

#endif	// HARE_WRAP_ICONV_H
