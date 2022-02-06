#include "test.h"

#include <hare/curl.h>
#include <hare/wrap/curl.h>
#include <hare/fstream>	// file_read

struct TestHareCurl {
	static void test_get() {
		EQUAL_D(CURLE_BAD_FUNCTION_ARGUMENT, hare::curl_set_url(NULL, "https://github.com/"));

		hare::wrap::CURL curl(::curl_easy_init());

		EQUAL_D(CURLE_OK, hare::curl_set_url(curl, CHAR_PTR_NULL));
		std::string data;
		long response_code = 0;
		EQUAL_D(CURLE_COULDNT_RESOLVE_HOST, hare::curl_get(curl, "http://host.does.not.exist/", data));
		EQUAL_S("", data);

		EQUAL_D(CURLE_OK, hare::curl_get(curl, "https://github.com/does.not.exist", data));
		EQUAL_D(CURLE_OK, ::curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &response_code));
		EQUAL_D(404, response_code);
		EQUAL_S("Not Found", data);

		data.clear();
		EQUAL_D(CURLE_OK, hare::curl_get(curl, "https://raw.githubusercontent.com/hareat/libhare/main/test/data/readonly.txt", data));
		EQUAL_D(CURLE_OK, ::curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &response_code));
		EQUAL_D(200, response_code);
		EQUAL_S(hare::fstream::read("data/readonly.txt"), data);
	}

	static void test_head() {
		hare::wrap::CURL curl(::curl_easy_init());

		long response_code = 0;
		EQUAL_D(CURLE_OK, hare::curl_head(curl, "https://github.com/does.not.exist"));
		EQUAL_D(CURLE_OK, ::curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &response_code));
		EQUAL_D(404, response_code);

		EQUAL_D(CURLE_OK, hare::curl_head(curl, "https://raw.githubusercontent.com/hareat/libhare/main/test/data/readonly.txt"));
		EQUAL_D(CURLE_OK, ::curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &response_code));
		EQUAL_D(200, response_code);
	}

	static void test() {
		test_get();
		test_head();
	}
};
