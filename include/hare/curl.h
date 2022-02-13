#ifndef HARE_CURL_H
#define HARE_CURL_H

#include <curl/curl.h>

/***************************************************************
 * hare/curl.h handy convenience methods for curl.h.
 *
 * https://curl.se/libcurl/c/
 *
 * @author Hannes Reisinger github@HaRe.at
 ***************************************************************/

#include <string>

namespace hare {
	inline const char* to_sz(const CURLoption option) {
		switch (option) {
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
			case CURLOPT_READDATA:
				return "CURLOPT_READDATA";
			case CURLOPT_ERRORBUFFER:
				return "CURLOPT_ERRORBUFFER";
			case CURLOPT_WRITEFUNCTION:
				return "CURLOPT_WRITEFUNCTION";
			case CURLOPT_READFUNCTION:
				return "CURLOPT_READFUNCTION";
			case CURLOPT_TIMEOUT:
				return "CURLOPT_TIMEOUT";
			case CURLOPT_INFILESIZE:
				return "CURLOPT_INFILESIZE";
			case CURLOPT_POSTFIELDS:
				return "CURLOPT_POSTFIELDS";
			case CURLOPT_REFERER:
				return "CURLOPT_REFERER";
			case CURLOPT_FTPPORT:
				return "CURLOPT_FTPPORT";
			case CURLOPT_USERAGENT:
				return "CURLOPT_USERAGENT";
			case CURLOPT_LOW_SPEED_LIMIT:
				return "CURLOPT_LOW_SPEED_LIMIT";
			case CURLOPT_LOW_SPEED_TIME:
				return "CURLOPT_LOW_SPEED_TIME";
			case CURLOPT_RESUME_FROM:
				return "CURLOPT_RESUME_FROM";
			case CURLOPT_COOKIE:
				return "CURLOPT_COOKIE";
			case CURLOPT_HTTPHEADER:
				return "CURLOPT_HTTPHEADER";
			case CURLOPT_HTTPPOST:
				return "CURLOPT_HTTPPOST";
			case CURLOPT_SSLCERT:
				return "CURLOPT_SSLCERT";
			case CURLOPT_KEYPASSWD:
				return "CURLOPT_KEYPASSWD";
			case CURLOPT_CRLF:
				return "CURLOPT_CRLF";
			case CURLOPT_QUOTE:
				return "CURLOPT_QUOTE";
			case CURLOPT_HEADERDATA:
				return "CURLOPT_HEADERDATA";
			case CURLOPT_COOKIEFILE:
				return "CURLOPT_COOKIEFILE";
			case CURLOPT_SSLVERSION:
				return "CURLOPT_SSLVERSION";
			case CURLOPT_TIMECONDITION:
				return "CURLOPT_TIMECONDITION";
			case CURLOPT_TIMEVALUE:
				return "CURLOPT_TIMEVALUE";
			case CURLOPT_CUSTOMREQUEST:
				return "CURLOPT_CUSTOMREQUEST";
			case CURLOPT_STDERR:
				return "CURLOPT_STDERR";
			case CURLOPT_POSTQUOTE:
				return "CURLOPT_POSTQUOTE";
			case CURLOPT_VERBOSE:
				return "CURLOPT_VERBOSE";
			case CURLOPT_HEADER:
				return "CURLOPT_HEADER";
			case CURLOPT_NOPROGRESS:
				return "CURLOPT_NOPROGRESS";
			case CURLOPT_NOBODY:
				return "CURLOPT_NOBODY";
			case CURLOPT_FAILONERROR:
				return "CURLOPT_FAILONERROR";
			case CURLOPT_UPLOAD:
				return "CURLOPT_UPLOAD";
			case CURLOPT_POST:
				return "CURLOPT_POST";
			case CURLOPT_DIRLISTONLY:
				return "CURLOPT_DIRLISTONLY";
			case CURLOPT_APPEND:
				return "CURLOPT_APPEND";
			case CURLOPT_NETRC:
				return "CURLOPT_NETRC";
			case CURLOPT_FOLLOWLOCATION:
				return "CURLOPT_FOLLOWLOCATION";
			case CURLOPT_TRANSFERTEXT:
				return "CURLOPT_TRANSFERTEXT";
			case CURLOPT_PUT:
				return "CURLOPT_PUT";
			case CURLOPT_PROGRESSFUNCTION:
				return "CURLOPT_PROGRESSFUNCTION";
			case CURLOPT_PROGRESSDATA:
				return "CURLOPT_PROGRESSDATA";
			case CURLOPT_AUTOREFERER:
				return "CURLOPT_AUTOREFERER";
			case CURLOPT_PROXYPORT:
				return "CURLOPT_PROXYPORT";
			case CURLOPT_POSTFIELDSIZE:
				return "CURLOPT_POSTFIELDSIZE";
			case CURLOPT_HTTPGET:
				return "CURLOPT_HTTPGET";
			case CURLOPT_HTTPAUTH:
				return "CURLOPT_HTTPAUTH";
			case CURLOPT_SSH_AUTH_TYPES:
				return "CURLOPT_SSH_AUTH_TYPES";
			case CURLOPT_SSH_PUBLIC_KEYFILE:
				return "CURLOPT_SSH_PUBLIC_KEYFILE";
			case CURLOPT_SSH_PRIVATE_KEYFILE:
				return "CURLOPT_SSH_PRIVATE_KEYFILE";
			case CURLOPT_TIMEOUT_MS:
				return "CURLOPT_TIMEOUT_MS";
			case CURLOPT_CONNECTTIMEOUT_MS:
				return "CURLOPT_CONNECTTIMEOUT_MS";
			case CURLOPT_SSH_HOST_PUBLIC_KEY_MD5:
				return "CURLOPT_SSH_HOST_PUBLIC_KEY_MD5";
			case CURLOPT_USERNAME:
				return "CURLOPT_USERNAME";
			case CURLOPT_PASSWORD:
				return "CURLOPT_PASSWORD";
			case CURLOPT_SSH_KNOWNHOSTS:
				return "CURLOPT_SSH_KNOWNHOSTS";
			case CURLOPT_SSH_KEYFUNCTION:
				return "CURLOPT_SSH_KEYFUNCTION";
			case CURLOPT_SSH_KEYDATA:
				return "CURLOPT_SSH_KEYDATA";
			case CURLOPT_TRANSFER_ENCODING:
				return "CURLOPT_TRANSFER_ENCODING";
			case CURLOPT_DNS_SERVERS:
				return "CURLOPT_DNS_SERVERS";
			case CURLOPT_SSH_COMPRESSION:
				return "CURLOPT_SSH_COMPRESSION";
			case CURLOPT_SASL_AUTHZID:
				return "CURLOPT_SASL_AUTHZID";
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
	inline CURLcode curl_set_customrequest(CURL *curl, const char *request) {
		return ::curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, request);
	}
	inline CURLcode curl_set_customrequest(CURL *curl, const std::string& request) {
		return curl_set_url(curl, request.c_str());
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
	inline CURLcode curl_nobody(CURL *curl, const std::string& url) {
		CURLcode cc = curl_set_url(curl, url);
		if (cc != CURLE_OK)
			return cc;
		cc = ::curl_easy_setopt(curl, CURLOPT_NOBODY, 1L);
		if (cc != CURLE_OK)
			return cc;
		return ::curl_easy_perform(curl);
	}
	inline CURLcode curl_post(CURL *curl, const std::string& url, const std::string& data) {
		CURLcode cc = curl_set_url(curl, url);
		if (cc != CURLE_OK)
			return cc;
		cc = ::curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, data.size());
		if (cc != CURLE_OK)
			return cc;
		// CURLOPT_POSTFIELDS implies CURLOPT_POST
		cc = ::curl_easy_setopt(curl, CURLOPT_POSTFIELDS, data.c_str());
		if (cc != CURLE_OK)
			return cc;
		return ::curl_easy_perform(curl);
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
	inline CURLcode curl_set_httpget(CURL *curl, std::string& data) {
		const CURLcode cc = ::curl_easy_setopt(curl, CURLOPT_HTTPGET, 1L);
		if (cc != CURLE_OK)
			return cc;
		return curl_set_write(curl, data);
	}
	inline CURLcode curl_httpget(CURL *curl, const std::string& url, std::string& data) {
		CURLcode cc = curl_set_url(curl, url);
		if (cc != CURLE_OK)
			return cc;
		cc = curl_set_httpget(curl, data);
		if (cc != CURLE_OK)
			return cc;
		return ::curl_easy_perform(curl);
	}

	// similar to size_t fread(void *ptr, size_t size, size_t nmemb, FILE *stream)
	struct string_pos {
		string_pos(const std::string _str) : str(_str), pos(0) {}
		const std::string str;
		size_t pos;
	};
	inline size_t curl_read_from_string(char *chunk, size_t size, size_t nitems, string_pos *sender) {
		const size_t chunk_size = size * nitems;
		size_t chars_copied = 0;
		if (chunk && sender) {
			chars_copied = sender->str.copy(chunk, chunk_size, sender->pos);
			sender->pos += chars_copied;
		}
		return chars_copied;
	}
	inline CURLcode curl_set_read(CURL *curl, string_pos& data) {
		CURLcode cc = ::curl_easy_setopt(curl, CURLOPT_READDATA, &data);
		if (cc != CURLE_OK)
			return cc;
		cc = ::curl_easy_setopt(curl, CURLOPT_INFILESIZE, data.str.size());
		if (cc != CURLE_OK)
			return cc;
		return ::curl_easy_setopt(curl, CURLOPT_READFUNCTION, hare::curl_read_from_string);
	}
	inline CURLcode curl_set_upload(CURL *curl, string_pos& data) {
		const CURLcode cc = ::curl_easy_setopt(curl, CURLOPT_UPLOAD, 1L);
		if (cc != CURLE_OK)
			return cc;
		return curl_set_read(curl, data);
	}
	inline CURLcode curl_upload(CURL *curl, const std::string& url, const std::string& data) {
		CURLcode cc = curl_set_url(curl, url);
		if (cc != CURLE_OK)
			return cc;
		string_pos spdata(data);
		cc = curl_set_upload(curl, spdata);
		if (cc != CURLE_OK)
			return cc;
		return ::curl_easy_perform(curl);
	}

	// some wrappers with better known names
	inline CURLcode curl_head(CURL *curl, const std::string& url) {
		return curl_nobody(curl, url);
	}
	inline CURLcode curl_set_get(CURL *curl, std::string& data) {
		return curl_set_httpget(curl, data);
	}
	inline CURLcode curl_get(CURL *curl, const std::string& url, std::string& data) {
		return curl_httpget(curl, url, data);
	}
	// CURLOPT_PUT is deprecated
	inline CURLcode curl_set_put(CURL *curl, string_pos& data) {
		return curl_set_upload(curl, data);
	}
	inline CURLcode curl_put(CURL *curl, const std::string& url, const std::string& data) {
		return curl_upload(curl, url, data);
	}
}	// namespace hare

#endif	// HARE_CURL_H
