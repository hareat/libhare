#ifndef HARE_THROWS_CURL_H
#define HARE_THROWS_CURL_H

#include <curl/curl.h>

/***************************************************************************
 * Throws an exception (derived of std::system_error) in case of any error.
 *
 * @author Hannes Reisinger github@HaRe.at
 ***************************************************************************/

#include <hare/curl.h>
#include <hare/strprintf>
#include <hare/system_error>

namespace hare {
	/**********************************************************************
	 * CURL related error_category and error.
	 **********************************************************************/
	struct curl_error_category : public std::error_category {
		virtual const char* name() const noexcept { return "curl"; }
		virtual std::string message(int cc) const { return curl_easy_strerror((CURLcode) cc); }
	};

	struct curl_error : public backtrace_error {
		curl_error(const CURLcode cc) : backtrace_error(cc, curl_error_category()) {}
		curl_error(const CURLcode cc, const std::string& what) : backtrace_error(cc, curl_error_category(), what) {}
		curl_error(const CURLcode cc, const char *what) : backtrace_error(cc, curl_error_category(), what) {}
		template<typename ... Args>
		curl_error(const CURLcode cc, const char *format, Args ... args)
			: backtrace_error(cc, curl_error_category(), strprintf<256>(format, args ...)) {}

		CURLcode curlCode() const { return (CURLcode) code().value(); }
	};

	namespace throws {
		inline CURL* curl_easy_init() {
			CURL* const curl = ::curl_easy_init();
			if (!curl)
				throw std::runtime_error(strprintf<256>("%s() failed", __func__));
			return curl;
		}

		template<typename ... Args>
		inline void curl_easy_setopt(CURL *curl, CURLoption option, Args ... args) {
			CURLcode const cc = ::curl_easy_setopt(curl, option, args ...);
			if (cc != CURLE_OK)
				throw curl_error(cc, "%s(%d=%s) failed", __func__, option, hare::to_sz(option));
		}
		inline void curl_set_url(CURL *curl, const char *url) {
			CHECK_NOT_NULL_ARG1(url);
			CURLcode const cc = hare::curl_set_url(curl, url);
			if (cc != CURLE_OK)
				throw curl_error(cc, "%s(%s) failed", __func__, url);
		}
		inline void curl_set_url(CURL *curl, const std::string& url) {
			CURLcode const cc = hare::curl_set_url(curl, url);
			if (cc != CURLE_OK)
				throw curl_error(cc, "%s(%s) failed", __func__, url.c_str());
		}
		inline void curl_set_user_pwd(CURL *curl, const std::string& user, const std::string& pwd) {
			CURLcode const cc = hare::curl_set_user_pwd(curl, user, pwd);
			if (cc != CURLE_OK)
				throw curl_error(cc, "%s() failed", __func__);	// user and pwd are sensitive
		}
		inline void curl_set_auth_basic(CURL *curl) {
			CURLcode const cc = hare::curl_set_auth_basic(curl);
			if (cc != CURLE_OK)
				throw curl_error(cc, "%s() failed", __func__);
		}
		inline void curl_set_auth_basic(CURL *curl, const std::string& user, const std::string& pwd) {
			hare::throws::curl_set_auth_basic(curl);
			hare::throws::curl_set_user_pwd(curl, user, pwd);
		}
		inline void curl_set_auth_digest(CURL *curl) {
			CURLcode const cc = hare::curl_set_auth_digest(curl);
			if (cc != CURLE_OK)
				throw curl_error(cc, "%s() failed", __func__);
		}
		inline void curl_set_auth_digest(CURL *curl, const std::string& user, const std::string& pwd) {
			hare::throws::curl_set_auth_digest(curl);
			hare::throws::curl_set_user_pwd(curl, user, pwd);
		}
		// similar to size_t fwrite(const void *ptr, size_t size, size_t nmemb, FILE *stream)
		inline size_t curl_write_to_string(const char *chunk, size_t size, size_t nmemb, std::string *receiver) {
			CHECK_NOT_NULL_ARG2(chunk, receiver);
			const size_t chunk_size = size * nmemb;
			receiver->append(chunk, chunk_size);
			return chunk_size;
		}
		inline void curl_set_write(CURL *curl, std::string& data) {
			hare::throws::curl_easy_setopt(curl, CURLOPT_WRITEDATA, &data);
			hare::throws::curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, hare::throws::curl_write_to_string);
		}

		inline void curl_easy_perform(CURL *curl) {
			CURLcode const cc = ::curl_easy_perform(curl);
			if (cc != CURLE_OK)
				throw curl_error(cc, "%s() failed", __func__);
		}
		inline void curl_easy_perform(CURL *curl, const char *url) {
			hare::throws::curl_set_url(curl, url);
			CURLcode const cc = ::curl_easy_perform(curl);
			if (cc != CURLE_OK)
				throw curl_error(cc, "%s(%s) failed", __func__, url);
		}
		inline void curl_easy_perform(CURL *curl, const std::string& url) {
			hare::throws::curl_set_url(curl, url);
			CURLcode const cc = ::curl_easy_perform(curl);
			if (cc != CURLE_OK)
				throw curl_error(cc, "%s(%s) failed", __func__, url.c_str());
		}
		inline void curl_delete(CURL *curl, const std::string& url) {
			hare::throws::curl_set_url(curl, url);
			hare::throws::curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "DELETE");
			CURLcode const cc = ::curl_easy_perform(curl);
			if (cc != CURLE_OK)
				throw curl_error(cc, "%s(%s) failed", __func__, url.c_str());
		}
		inline void curl_post(CURL *curl, const std::string& url, const std::string& data) {
			hare::throws::curl_set_url(curl, url);
			hare::throws::curl_easy_setopt(curl, CURLOPT_POSTFIELDS, data.c_str());
			hare::throws::curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, data.size());
			CURLcode const cc = ::curl_easy_perform(curl);
			if (cc != CURLE_OK)
				throw curl_error(cc, "%s(%s) failed", __func__, url.c_str());	// data could be sensitive
		}
		inline void curl_put(CURL *curl, const std::string& url, const std::string& data) {
			hare::throws::curl_set_url(curl, url);
			hare::throws::curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "PUT");
			hare::throws::curl_easy_setopt(curl, CURLOPT_POSTFIELDS, data.c_str());
			hare::throws::curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, data.size());
			CURLcode const cc = ::curl_easy_perform(curl);
			if (cc != CURLE_OK)
				throw curl_error(cc, "%s(%s) failed", __func__, url.c_str());	// data could be sensitive
		}

		inline long curl_get_response_code(CURL *curl) {
			long response_code;
			CURLcode const cc = ::curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &response_code);
			if (cc != CURLE_OK)
				throw curl_error(cc, "%s() failed", __func__);
			return response_code;
		}
	}	// namespace throws
}	// namespace hare

#endif	// HARE_THROWS_CURL_H
