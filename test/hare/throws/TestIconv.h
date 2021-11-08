#include "test.h"

#include <hare/throws/iconv.h>

struct TestHareThrowsIconv {
	static void test_iconv_open() {
		try {
			hare::throws::iconv_open(CHAR_PTR_NULL, CHAR_PTR_NULL);
			FAIL("should not reach");
		} catch (const std::invalid_argument& ex) {
			EQUAL_S("iconv_open(tocode and fromcode are NULL)", ex.what());
		}
		try {
			hare::throws::iconv_open("foo", "bar");
			FAIL("should not reach");
		} catch (const hare::system_error& ex) {
			EQUAL_S("iconv_open(\"foo\", \"bar\") failed: Invalid argument", ex.what());
		}
	}

	static void test_iconv() {
		try {
			hare::throws::iconv((iconv_t) -1, nullptr, nullptr, nullptr, nullptr);
			FAIL("should not reach");
		} catch (const hare::system_error& ex) {
			EQUAL_S("iconv() failed: Bad file descriptor", ex.what());
		}
	}

	static void test_iconv_close() {
		try {
			hare::throws::iconv_close((iconv_t) -1);
			FAIL("should not reach");
		} catch (const hare::system_error& ex) {
			EQUAL_S("iconv_close() failed: Bad file descriptor", ex.what());
		}
	}

	static void test() {
		test_iconv_open();
		test_iconv();
		test_iconv_close();
	}
};
