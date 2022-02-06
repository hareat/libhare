#include "test.h"

#include <hare/throws/curl.h>
#include <hare/wrap/curl.h>
#include <hare/fstream>	// file_read

struct TestHareThrowsCurl {
	static void test_get() {
		hare::wrap::CURL curl(hare::throws::curl_easy_init());

		try {
			hare::throws::curl_set_url(NULL, "https://github.com/");
			FAIL("should not reach");
		} catch (const std::invalid_argument& ex) {
			EQUAL_S("curl_set_url(curl is NULL)", ex.what());
		}
		try {
			hare::throws::curl_easy_perform(curl, "http://host.does.not.exist/");
			FAIL("should not reach");
		} catch (const hare::curl_error& ex) {
			EQUAL_S("curl_easy_perform(\"http://host.does.not.exist/\") failed: Couldn't resolve host name", ex.what());
		}
		std::string data;
		hare::throws::curl_set_write(curl, data);
		hare::throws::curl_easy_perform(curl, "https://raw.githubusercontent.com/hareat/libhare/main/test/data/readonly.txt");
		EQUAL_D(200, hare::throws::curl_get_response_code(curl));
		EQUAL_S(hare::fstream::read("data/readonly.txt"), data);
	}

	static void test_head() {
	}

	static void test() {
		test_get();
		test_head();
	}
};
