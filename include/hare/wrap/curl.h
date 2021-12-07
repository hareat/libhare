#ifndef HARE_WRAP_CURL_H
#define HARE_WRAP_CURL_H

#include <curl/curl.h>

/***************************************************************************
 * hare/warp/curl.h some wrappers for curl.h.
 *
 * Encapsulates std C pointers to ensure cleanup/free is called also in case
 * of an exception.
 *
 * @usage
 * 	const hare::wrap::CURL curl(curl_easy_init());
 *	if (!curl)
 *		exit(EXIT_FAILURE);
 *	else {
 *		curl_easy_setopt(curl, ...);
 *		...
 *	<automatically cleanup the CURL pointer also in case of an exception>
 * or simpler
 * 	const hare::wrap::CURL curl(hare::throws::curl_easy_init());
 *	hare::throws::curl_easy_setopt(curl, ...);
 *	...
 *	<automatically cleanup the CURL pointer also in case of an exception>
 *
 * @author Hannes Reisinger github@HaRe.at
 ***************************************************************************/

namespace hare {
	namespace wrap {
		/******************************************************************
		 * hare::wrap::CURL encapsulates a std C CURL pointer to ensure
		 * curl_easy_cleanup() is called also in case of an exception.
		 ******************************************************************/
		class CURL {
			::CURL *m_curl;	// the encapsulated std C CURL pointer
		public:
			CURL() : m_curl(0) {}
			CURL(::CURL *curl) : m_curl(curl) {}

			~CURL() { if (m_curl) ::curl_easy_cleanup(m_curl); }

			CURL& operator=(::CURL *curl) {
				if (m_curl)
					::curl_easy_cleanup(m_curl);
				m_curl = curl;
				return *this;
			}

			// use std::shared_ptr instead
			CURL(const CURL&) = delete;
			CURL& operator=(const CURL&) = delete;

			void curl_easy_cleanup() {
				if (m_curl) {
					::curl_easy_cleanup(m_curl);
					m_curl = 0;
				}
			}

			// to use it like a std C CURL pointer
			operator ::CURL*() const { return m_curl; }
		};
	}	// namespace wrap
}	// namespace hare


// to avoid accidentally calls
void curl_easy_cleanup(hare::wrap::CURL &curl) { curl.curl_easy_cleanup(); }

#endif	// HARE_WRAP_CURL_H
