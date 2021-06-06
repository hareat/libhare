#include "test.h"

#include <hare/cstring>

struct TestHareCstring {
	static void test_strcmp() {
		EQUAL_D( 1, hare::strcmp("b", "a"));
		EQUAL_D( 0, hare::strcmp("a", "a"));
		EQUAL_D(-1, hare::strcmp("a", "b"));
		// Segmentation fault: EQUAL_D(1, std::strcmp("", NULL));
		EQUAL_D(-1, hare::strcmp(CHAR_PTR_NULL, ""));
		EQUAL_D( 1, hare::strcmp("", CHAR_PTR_NULL));
		EQUAL_D( 0, hare::strcmp(CHAR_PTR_NULL, CHAR_PTR_NULL));
	}

	static void test_memchr() {
		EQUAL_D(NULL, std::memchr(CHAR_PTR_NULL, 'x', 0));
		// Segmentation fault: EQUAL_D(NULL, std::memchr((void*) 0, 'x', 1));
	}

	static void test_strcat() {
		// Segmentation fault: EQUAL_D(NULL, std::strcat(NULL, "test"));
	}

	static void test_strlen() {
		EQUAL_D(0, std::strlen(""));
		// Segmentation fault: EQUAL_D(0, std::strlen(NULL));
		EQUAL_D(0, hare::strlen(NULL));
	}

	static void test() {
		test_strcmp();
		test_memchr();
		test_strcat();
		test_strlen();
	}
};