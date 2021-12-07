#ifndef HARE_ICONV_H
#define HARE_ICONV_H

#include <iconv.h>

/***************************************************************
 * hare/iconv.h handy convenience methods for iconv.h.
 *
 * https://de.wikipedia.org/wiki/ISO_8859
 *
 * @author Hannes Reisinger github@HaRe.at
 ***************************************************************/

#include <string>
#include <hare/system_error>

// To avoid typos.
// see https://www.charset.org/utf-8
// and https://www.charset.org/charsets/iso-8859-1
#define UTF8 "UTF-8"
#define ISO88591 "ISO-8859-1"

namespace hare {
	class Iconv {
		const std::string m_to, m_from; // remember for error messages
		const iconv_t m_cd; // the encapsulated conversion descriptor
		const size_t m_multiplier; // one UTF-8 character can need up to 4 bytes
	public:
		Iconv(const char *to, const char *from, size_t multiplier)
			: m_to(to), m_from(from), m_cd(iconv_open(to, from)), m_multiplier(multiplier) {
			if (m_cd == ((iconv_t) -1))
				throw hare::system_error("%s(\"%s\", \"%s\", %zu) failed", __func__, to, from, multiplier);
		}
		~Iconv() { iconv_close(m_cd); }

		std::string operator()(std::string in) const {
			size_t inbytesleft = in.length();
			char *inbuf = &in[0];
			size_t outbytesleft = m_multiplier * inbytesleft + 1;
			std::string out;
			out.resize(outbytesleft);
			char *outbuf = &out[0];
			if (iconv(m_cd, &inbuf, &inbytesleft, &outbuf, &outbytesleft) == ((size_t) -1))
				throw hare::system_error(m_from + " to " + m_to + " failed");
			out.resize(out.length() - outbytesleft);
			return out;
		}
	};
}	// namespace hare

#endif	// HARE_ICONV_H
