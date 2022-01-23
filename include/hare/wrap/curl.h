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

#include <hare/stdexcept>

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

		/******************************************************************
		 * hare::wrap::curl_slist encapsulates a std C curl_slist pointer to
		 * ensure curl_slist_free_all() is called also in case of an exception.
		 ******************************************************************/
		class curl_slist {
			::curl_slist *m_curl_slist;	// the encapsulated std C curl_slist pointer
		public:
			curl_slist() : m_curl_slist(0) {}
			curl_slist(::curl_slist *list) : m_curl_slist(list) {}

			~curl_slist() { if (m_curl_slist) ::curl_slist_free_all(m_curl_slist); }

			// use std::shared_ptr instead
			curl_slist(const curl_slist&) = delete;
			curl_slist& operator=(const curl_slist&) = delete;

			::curl_slist* curl_slist_append(const char *string) {
				::curl_slist *tmp = ::curl_slist_append(m_curl_slist, string);
				if (tmp)
					m_curl_slist = tmp;
				return tmp;
			}

			void curl_slist_free_all() {
				if (m_curl_slist) {
					::curl_slist_free_all(m_curl_slist);
					m_curl_slist = 0;
				}
			}

			// to use it like a std C curl_slist pointer
			operator ::curl_slist*() const { return m_curl_slist; }
			::curl_slist* get() const { return m_curl_slist; }
		};
	}	// namespace wrap

	namespace throws {
		inline ::curl_slist* curl_slist_append(hare::wrap::curl_slist &list, const char *string) {
			::curl_slist *result = list.curl_slist_append(string);
			if (result == NULL)
				throw hare::runtime_error("%s(%s) failed", __func__, string);
			return result;
		}
	}	// namespace throws
}	// namespace hare


// to avoid accidentally calls
inline void curl_easy_cleanup(hare::wrap::CURL &curl) { curl.curl_easy_cleanup(); }
inline ::curl_slist* curl_slist_append(hare::wrap::curl_slist &list, const char *string) { return list.curl_slist_append(string); }
inline void curl_slist_free_all(hare::wrap::curl_slist &list) { list.curl_slist_free_all(); }

#endif	// HARE_WRAP_CURL_H
