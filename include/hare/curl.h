#ifndef HARE_CURL_H
#define HARE_CURL_H

#include <curl/curl.h>

/***************************************************************
 * hare/curl.h handy convenience methods for curl.h.
 *
 * @author Hannes Reisinger github@HaRe.at
 ***************************************************************/

#include <string>

namespace hare {
	inline const char* to_sz(const CURLoption cc) {
		switch (cc) {
			case CURLOPT_WRITEDATA:
				return "CURLOPT_WRITEDATA";
			case CURLOPT_URL:
				return "CURLOPT_URL";
			case CURLOPT_PORT:
				return "CURLOPT_PORT";
			case CURLOPT_PROXY:
				return "CURLOPT_PROXY";
			case CURLOPT_USERPWD:
				return "CURLOPT_USERPWD";
			case CURLOPT_PROXYUSERPWD:
				return "CURLOPT_PROXYUSERPWD";
			case CURLOPT_RANGE:
				return "CURLOPT_RANGE";
//...
			case CURLOPT_HTTPAUTH:
				return "CURLOPT_HTTPAUTH";
//...
			default:
				return "unknown";
		}
	}

	inline CURLcode curl_set_url(CURL *curl, const char *url) {
		return ::curl_easy_setopt(curl, CURLOPT_URL, url);
	}
	inline CURLcode curl_set_url(CURL *curl, const std::string& url) {
		return curl_set_url(curl, url.c_str());
	}
	inline CURLcode curl_set_user_pwd(CURL *curl, const std::string& user, const std::string& pwd) {
		return ::curl_easy_setopt(curl, CURLOPT_USERPWD, (user + ":" + pwd).c_str());
	}
	inline CURLcode curl_set_auth_basic(CURL *curl) {
		return ::curl_easy_setopt(curl, CURLOPT_HTTPAUTH, CURLAUTH_BASIC);
	}
	inline CURLcode curl_set_auth_digest(CURL *curl) {
		return ::curl_easy_setopt(curl, CURLOPT_HTTPAUTH, CURLAUTH_DIGEST);
	}
	inline CURLcode curl_set_auth_basic(CURL *curl, const std::string& user, const std::string& pwd) {
		const CURLcode cc = curl_set_auth_basic(curl);
		if (cc != CURLE_OK)
			return cc;
		return curl_set_user_pwd(curl, user, pwd);
	}
	inline CURLcode curl_set_auth_digest(CURL *curl, const std::string& user, const std::string& pwd) {
		const CURLcode cc = curl_set_auth_digest(curl);
		if (cc != CURLE_OK)
			return cc;
		return curl_set_user_pwd(curl, user, pwd);
	}
	// similar to size_t fwrite(const void *ptr, size_t size, size_t nmemb, FILE *stream)
	inline size_t curl_write_to_string(const char *chunk, size_t size, size_t nmemb, std::string *receiver) {
		const size_t chunk_size = size * nmemb;
		if (chunk && receiver)
			receiver->append(chunk, chunk_size);
		return chunk_size;
	}
	inline CURLcode curl_set_write(CURL *curl, std::string& data) {
		const CURLcode cc = ::curl_easy_setopt(curl, CURLOPT_WRITEDATA, &data);
		if (cc != CURLE_OK)
			return cc;
		return ::curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, hare::curl_write_to_string);
	}
}	// namespace hare

#endif	// HARE_CURL_H
