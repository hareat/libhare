#include "test.h"

#include <hare/throws/cstdlib>

struct TestHareThrowsCstdlib {
	static void test_getenv() {
		// Segmentation fault: std::getenv(NULL);
		try {
			hare::throws::getenv(NULL);
			FAIL("should not reach");
		} catch (const std::invalid_argument& ex) {
			EQUAL_S("getenv(key is NULL)", ex.what());
		}

		EQUAL_D(NULL, hare::throws::getenv("does not exist"));
		try {
			hare::throws::getenv_mandatory("does not exist");
			FAIL("should not reach");
		} catch (const std::runtime_error& ex) {
			EQUAL_S("getenv_mandatory(does not exist) result is NULL", ex.what());
		}
	}

	static void test_putenv() {
		// Segmentation fault: putenv(NULL);
		try {
			hare::throws::putenv(CHAR_PTR_NULL);
			FAIL("should not reach");
		} catch (const std::invalid_argument& ex) {
			EQUAL_S("putenv(key_value is NULL)", ex.what());
		}
	}

	static void test_setenv() {
		setenv(CHAR_PTR_NULL, CHAR_PTR_NULL, true);	// strerror: Invalid argument
		try {
			hare::throws::setenv(CHAR_PTR_NULL, CHAR_PTR_NULL, false);
			FAIL("should not reach");
		} catch (const std::invalid_argument& ex) {
			EQUAL_S("setenv(key and value are NULL)", ex.what());
		}
	}

	static void test_unsetenv() {
		unsetenv(CHAR_PTR_NULL);	// strerror: Invalid argument
		try {
			hare::throws::unsetenv(CHAR_PTR_NULL);
			FAIL("should not reach");
		} catch (const std::invalid_argument& ex) {
			EQUAL_S("unsetenv(key is NULL)", ex.what());
		}
	}

	static void test() {
		test_getenv();
		test_putenv();
		test_setenv();
		test_unsetenv();
	}
};
