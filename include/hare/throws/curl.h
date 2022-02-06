#ifndef HARE_THROWS_CURL_H
#define HARE_THROWS_CURL_H

#include <curl/curl.h>

/***************************************************************************
 * Throws an exception (derived of std::system_error) in case of any error.
 *
 * @author Hannes Reisinger github@HaRe.at
 ***************************************************************************/

#include <hare/curl.h>
#include <hare/execinfo.h>	// backtrace
#include <hare/stdexcept>
#include <hare/strprintf>

#include <system_error>

namespace hare {
	/**********************************************************************
	 * CURL related error_category and error.
	 **********************************************************************/
	struct curl_error_category : public std::error_category {
		virtual const char* name() const noexcept { return "curl"; }
		virtual std::string message(int cc) const { return curl_easy_strerror((CURLcode) cc); }
	};

	struct curl_error : public std::system_error, public hare::backtrace {
		curl_error(const CURLcode cc) : std::system_error(cc, curl_error_category()) {}
		curl_error(const CURLcode cc, const std::string& what) : std::system_error(cc, curl_error_category(), what) {}
		curl_error(const CURLcode cc, const char *what) : std::system_error(cc, curl_error_category(), what) {}
		template<typename ... Args>
		curl_error(const CURLcode cc, const char *format, Args ... args)
			: std::system_error(cc, curl_error_category(), strprintf<256>(format, args ...)) {}

		CURLcode curlCode() const { return (CURLcode) code().value(); }
	};

	namespace throws {
		inline CURL* curl_easy_init() {
			CURL* const curl = ::curl_easy_init();
			if (!curl)
				throw std::runtime_error(strprintf<256>("%s() failed", __func__));
			return curl;
		}

		// there is not really a need for CHECK_NOT_NULL_ARG1(curl);
		// because if NULL CURLE_BAD_FUNCTION_ARGUMENT would be returned
		template<typename ... Args>
		inline void curl_easy_setopt(CURL *curl, CURLoption option, Args ... args) {
			CHECK_NOT_NULL_ARG1(curl);
			CURLcode const cc = ::curl_easy_setopt(curl, option, args ...);
			if (cc != CURLE_OK)
				throw curl_error(cc, "%s(%d=%s) failed", __func__, option, hare::to_sz(option));
		}
		inline void curl_easy_setopt(CURL *curl, CURLoption option, long l) {
			CHECK_NOT_NULL_ARG1(curl);
			CURLcode const cc = ::curl_easy_setopt(curl, option, l);
			if (cc != CURLE_OK)
				throw curl_error(cc, "%s(%d=%s, %ld) failed", __func__, option, hare::to_sz(option), l);
		}
		inline void curl_set_url(CURL *curl, const char *url) {
			CHECK_NOT_NULL_ARG1(curl);
			CURLcode const cc = hare::curl_set_url(curl, url);
			if (cc != CURLE_OK)
				throw curl_error(cc, "%s(\"%s\") failed", __func__, url);
		}
		inline void curl_set_url(CURL *curl, const std::string& url) {
			curl_set_url(curl, url.c_str());
		}
		inline void curl_set_user_pwd(CURL *curl, const std::string& user, const std::string& pwd) {
			CHECK_NOT_NULL_ARG1(curl);
			CURLcode const cc = hare::curl_set_user_pwd(curl, user, pwd);
			if (cc != CURLE_OK)
				throw curl_error(cc, "%s() failed", __func__);	// user and pwd are sensitive
		}
		inline void curl_set_auth_basic(CURL *curl) {
			CHECK_NOT_NULL_ARG1(curl);
			CURLcode const cc = hare::curl_set_auth_basic(curl);
			if (cc != CURLE_OK)
				throw curl_error(cc, "%s() failed", __func__);
		}
		inline void curl_set_auth_basic(CURL *curl, const std::string& user, const std::string& pwd) {
			CHECK_NOT_NULL_ARG1(curl);
			CURLcode cc = hare::curl_set_auth_basic(curl);
			if (cc != CURLE_OK)
				throw curl_error(cc, "%s() %s failed", __func__, "curl_set_auth_basic");
			cc = hare::curl_set_user_pwd(curl, user, pwd);
			if (cc != CURLE_OK)
				throw curl_error(cc, "%s() %s failed", __func__, "curl_set_user_pwd");	// user and pwd are sensitive
		}
		inline void curl_set_auth_digest(CURL *curl) {
			CHECK_NOT_NULL_ARG1(curl);
			CURLcode const cc = hare::curl_set_auth_digest(curl);
			if (cc != CURLE_OK)
				throw curl_error(cc, "%s() failed", __func__);
		}
		inline void curl_set_auth_digest(CURL *curl, const std::string& user, const std::string& pwd) {
			CHECK_NOT_NULL_ARG1(curl);
			CURLcode cc = hare::curl_set_auth_digest(curl);
			if (cc != CURLE_OK)
				throw curl_error(cc, "%s() %s failed", __func__, "curl_set_auth_digest");
			cc = hare::curl_set_user_pwd(curl, user, pwd);
			if (cc != CURLE_OK)
				throw curl_error(cc, "%s() %s failed", __func__, "curl_set_user_pwd");	// user and pwd are sensitive
		}
		inline void curl_easy_perform(CURL *curl) {
			CHECK_NOT_NULL_ARG1(curl);
			CURLcode const cc = ::curl_easy_perform(curl);
			if (cc != CURLE_OK)
				throw curl_error(cc, "%s() failed", __func__);
		}
		inline void curl_easy_perform(CURL *curl, const char *url) {
			CHECK_NOT_NULL_ARG2(curl, url);
			CURLcode cc = hare::curl_set_url(curl, url);
			if (cc != CURLE_OK)
				throw curl_error(cc, "%s(\"%s\") %s failed", __func__, url, "curl_set_url");
			cc = ::curl_easy_perform(curl);
			if (cc != CURLE_OK)
				throw curl_error(cc, "%s(\"%s\") failed", __func__, url);
		}
		inline void curl_easy_perform(CURL *curl, const std::string& url) {
			curl_easy_perform(curl, url.c_str());
		}
		inline long curl_get_response_code(CURL *curl) {
			CHECK_NOT_NULL_ARG1(curl);
			long response_code = 0;
			CURLcode const cc = ::curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &response_code);
			if (cc != CURLE_OK)
				throw curl_error(cc, "%s() failed", __func__);
			return response_code;
		}
		inline void curl_nobody(CURL *curl, const char *url) {
			CHECK_NOT_NULL_ARG2(curl, url);
			CURLcode cc = hare::curl_set_url(curl, url);
			if (cc != CURLE_OK)
				throw curl_error(cc, "%s(\"%s\") %s failed", __func__, url, "curl_set_url");
			cc = ::curl_easy_setopt(curl, CURLOPT_NOBODY, 1L);
			if (cc != CURLE_OK)
				throw curl_error(cc, "%s(\"%s\") %s failed", __func__, url, "CURLOPT_NOBODY");
			cc = ::curl_easy_perform(curl);
			if (cc != CURLE_OK)
				throw curl_error(cc, "%s(\"%s\") %s failed", __func__, url, "curl_easy_perform");
		}
		inline void curl_nobody(CURL *curl, const std::string& url) {
			curl_nobody(curl, url.c_str());
		}
		inline void curl_post(CURL *curl, const char *url, const std::string& data) {
			CHECK_NOT_NULL_ARG2(curl, url);
			CURLcode cc = hare::curl_set_url(curl, url);
			if (cc != CURLE_OK)
				// do not throw the data because it could be sensitive
				throw curl_error(cc, "%s(\"%s\") %s failed", __func__, url, "curl_set_url");
			cc = ::curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, data.size());
			if (cc != CURLE_OK)
				throw curl_error(cc, "%s(\"%s\") %s %zu failed", __func__, url, "CURLOPT_POSTFIELDSIZE", data.size());
			// CURLOPT_POSTFIELDS implies CURLOPT_POST
			cc = ::curl_easy_setopt(curl, CURLOPT_POSTFIELDS, data.c_str());
			if (cc != CURLE_OK)
				throw curl_error(cc, "%s(\"%s\") %s failed", __func__, url, "CURLOPT_POSTFIELDS");
			cc = ::curl_easy_perform(curl);
			if (cc != CURLE_OK)
				throw curl_error(cc, "%s(\"%s\") %s failed", __func__, url, "curl_easy_perform");
		}
		inline void curl_post(CURL *curl, const std::string& url, const std::string& data) {
			curl_post(curl, url.c_str(), data);
		}

		// similar to size_t fwrite(const void *ptr, size_t size, size_t nmemb, FILE *stream)
		inline size_t curl_write_to_string(const char *chunk, size_t size, size_t nmemb, std::string *receiver) {
			CHECK_NOT_NULL_ARG2(chunk, receiver);
			const size_t chunk_size = size * nmemb;
			receiver->append(chunk, chunk_size);
			return chunk_size;
		}
		inline void curl_set_write(CURL *curl, std::string& data) {
			CHECK_NOT_NULL_ARG1(curl);
			CURLcode cc = ::curl_easy_setopt(curl, CURLOPT_WRITEDATA, &data);
			if (cc != CURLE_OK)
				throw curl_error(cc, "%s() %s failed", __func__, "CURLOPT_WRITEDATA");
			cc = ::curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, hare::throws::curl_write_to_string);
			if (cc != CURLE_OK)
				throw curl_error(cc, "%s() %s failed", __func__, "CURLOPT_WRITEFUNCTION");
		}
		inline void curl_httpget(CURL *curl, const char *url, std::string& data) {
			CHECK_NOT_NULL_ARG2(curl, url);
			CURLcode cc = hare::curl_set_url(curl, url);
			if (cc != CURLE_OK)
				throw curl_error(cc, "%s(\"%s\") %s failed", __func__, url, "curl_set_url");
			cc = ::curl_easy_setopt(curl, CURLOPT_HTTPGET, 1L);
			if (cc != CURLE_OK)
				throw curl_error(cc, "%s(\"%s\") %s failed", __func__, url, "CURLOPT_HTTPGET");
			cc = ::curl_easy_setopt(curl, CURLOPT_WRITEDATA, &data);
			if (cc != CURLE_OK)
				throw curl_error(cc, "%s(\"%s\") %s failed", __func__, url, "CURLOPT_WRITEDATA");
			cc = ::curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, hare::throws::curl_write_to_string);
			if (cc != CURLE_OK)
				throw curl_error(cc, "%s(\"%s\") %s failed", __func__, url, "CURLOPT_WRITEFUNCTION");
			cc = ::curl_easy_perform(curl);
			if (cc != CURLE_OK)
				throw curl_error(cc, "%s(\"%s\") %s failed", __func__, url, "curl_easy_perform");
		}
		inline void curl_httpget(CURL *curl, const std::string& url, std::string& data) {
			curl_httpget(curl, url.c_str(), data);
		}

		// similar to size_t fread(void *ptr, size_t size, size_t nmemb, FILE *stream)
		inline size_t curl_read_from_string(char *chunk, size_t size, size_t nitems, hare::string_pos *sender) {
			CHECK_NOT_NULL_ARG2(chunk, sender);
			const size_t chunk_size = size * nitems;
			const size_t chars_copied = sender->str.copy(chunk, chunk_size, sender->pos);
			sender->pos += chars_copied;
			return chars_copied;
		}
		inline void curl_set_read(CURL *curl, hare::string_pos& data) {
			CURLcode cc = ::curl_easy_setopt(curl, CURLOPT_READDATA, &data);
			if (cc != CURLE_OK)
				throw curl_error(cc, "%s() %s failed", __func__, "CURLOPT_READDATA");
			cc = ::curl_easy_setopt(curl, CURLOPT_INFILESIZE, data.str.size());
			if (cc != CURLE_OK)
				throw curl_error(cc, "%s() %s %zu failed", __func__, "CURLOPT_INFILESIZE", data.str.size());
			cc = ::curl_easy_setopt(curl, CURLOPT_READFUNCTION, hare::curl_read_from_string);
			if (cc != CURLE_OK)
				throw curl_error(cc, "%s() %s failed", __func__, "CURLOPT_READFUNCTION");
		}
		inline void curl_upload(CURL *curl, const char *url, const std::string& data) {
			CHECK_NOT_NULL_ARG2(curl, url);
			CURLcode cc = hare::curl_set_url(curl, url);
			if (cc != CURLE_OK)
				// do not throw the data because it could be sensitive
				throw curl_error(cc, "%s(\"%s\") %s failed", __func__, url, "curl_set_url");
			cc = ::curl_easy_setopt(curl, CURLOPT_UPLOAD, 1L);
			if (cc != CURLE_OK)
				throw curl_error(cc, "%s(\"%s\") %s failed", __func__, url, "CURLOPT_UPLOAD");
			hare::string_pos spdata(data);
			cc = ::curl_easy_setopt(curl, CURLOPT_READDATA, &spdata);
			if (cc != CURLE_OK)
				throw curl_error(cc, "%s(\"%s\") %s failed", __func__, url, "CURLOPT_READDATA");
			cc = ::curl_easy_setopt(curl, CURLOPT_INFILESIZE, data.size());
			if (cc != CURLE_OK)
				throw curl_error(cc, "%s(\"%s\") %s %zu failed", __func__, url, "CURLOPT_INFILESIZE", data.size());
			cc = ::curl_easy_setopt(curl, CURLOPT_READFUNCTION, hare::throws::curl_read_from_string);
			if (cc != CURLE_OK)
				throw curl_error(cc, "%s(\"%s\") %s failed", __func__, url, "CURLOPT_READFUNCTION");
			cc = ::curl_easy_perform(curl);
			if (cc != CURLE_OK)
				throw curl_error(cc, "%s(\"%s\") %s failed", __func__, url, "curl_easy_perform");
		}
		inline void curl_upload(CURL *curl, const std::string& url, const std::string& data) {
			curl_upload(curl, url.c_str(), data);
		}

		// some wrappers with better known names
		inline void curl_head(CURL *curl, const char *url) {
			CHECK_NOT_NULL_ARG2(curl, url);
			CURLcode cc = hare::curl_set_url(curl, url);
			if (cc != CURLE_OK)
				throw curl_error(cc, "%s(\"%s\") %s failed", __func__, url, "curl_set_url");
			cc = ::curl_easy_setopt(curl, CURLOPT_NOBODY, 1L);
			if (cc != CURLE_OK)
				throw curl_error(cc, "%s(\"%s\") %s failed", __func__, url, "curl_easy_setopt");
			cc = ::curl_easy_perform(curl);
			if (cc != CURLE_OK)
				throw curl_error(cc, "%s(\"%s\") %s failed", __func__, url, "curl_easy_perform");
		}
		inline void curl_head(CURL *curl, const std::string& url) {
			curl_head(curl, url.c_str());
		}
		inline void curl_get(CURL *curl, const char *url, std::string& data) {
			CHECK_NOT_NULL_ARG2(curl, url);
			CURLcode cc = hare::curl_set_url(curl, url);
			if (cc != CURLE_OK)
				throw curl_error(cc, "%s(\"%s\") %s failed", __func__, url, "curl_set_url");
			cc = ::curl_easy_setopt(curl, CURLOPT_HTTPGET, 1L);
			if (cc != CURLE_OK)
				throw curl_error(cc, "%s(\"%s\") %s failed", __func__, url, "CURLOPT_HTTPGET");
			cc = ::curl_easy_setopt(curl, CURLOPT_WRITEDATA, &data);
			if (cc != CURLE_OK)
				throw curl_error(cc, "%s(\"%s\") %s failed", __func__, url, "CURLOPT_WRITEDATA");
			cc = ::curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, hare::throws::curl_write_to_string);
			if (cc != CURLE_OK)
				throw curl_error(cc, "%s(\"%s\") %s failed", __func__, url, "CURLOPT_WRITEFUNCTION");
			cc = ::curl_easy_perform(curl);
			if (cc != CURLE_OK)
				throw curl_error(cc, "%s(\"%s\") %s failed", __func__, url, "curl_easy_perform");
		}
		inline void curl_get(CURL *curl, const std::string& url, std::string& data) {
			curl_get(curl, url.c_str(), data);
		}
		inline void curl_put(CURL *curl, const char *url, const std::string& data) {
			CHECK_NOT_NULL_ARG2(curl, url);
			CURLcode cc = hare::curl_set_url(curl, url);
			if (cc != CURLE_OK)
				// do not throw the data because it could be sensitive
				throw curl_error(cc, "%s(\"%s\") %s failed", __func__, url, "curl_set_url");
			cc = ::curl_easy_setopt(curl, CURLOPT_UPLOAD, 1L);
			if (cc != CURLE_OK)
				throw curl_error(cc, "%s(\"%s\") %s failed", __func__, url, "CURLOPT_UPLOAD");
			hare::string_pos spdata(data);
			cc = ::curl_easy_setopt(curl, CURLOPT_READDATA, &spdata);
			if (cc != CURLE_OK)
				throw curl_error(cc, "%s(\"%s\") %s failed", __func__, url, "CURLOPT_READDATA");
			cc = ::curl_easy_setopt(curl, CURLOPT_INFILESIZE, data.size());
			if (cc != CURLE_OK)
				throw curl_error(cc, "%s(\"%s\") %s %zu failed", __func__, url, "CURLOPT_INFILESIZE", data.size());
			cc = ::curl_easy_setopt(curl, CURLOPT_READFUNCTION, hare::throws::curl_read_from_string);
			if (cc != CURLE_OK)
				throw curl_error(cc, "%s(\"%s\") %s failed", __func__, url, "CURLOPT_READFUNCTION");
			cc = ::curl_easy_perform(curl);
			if (cc != CURLE_OK)
				throw curl_error(cc, "%s(\"%s\") %s failed", __func__, url, "curl_easy_perform");
		}
		inline void curl_put(CURL *curl, const std::string& url, const std::string& data) {
			curl_put(curl, url.c_str(), data);
		}

		inline ::curl_slist* curl_slist_append(::curl_slist *csl, const char *string) {
			CHECK_NOT_NULL_ARG1(string);
			::curl_slist *result = ::curl_slist_append(csl, string);
			if (result == NULL)
				throw hare::runtime_error("%s(%s) failed", __func__, string);
			return result;
		}
	}	// namespace throws
}	// namespace hare

#endif	// HARE_THROWS_CURL_H
