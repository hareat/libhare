#include "test.h"

#include <hare/cstring>

struct TestHareCstring {
	static void test_strcmp() {
		EQUAL_D(-1, hare::strcmp("a", "b"));
		EQUAL_D( 1, hare::strcmp("b", "a"));
		EQUAL_D( 0, hare::strcmp("a", "a"));
		// Segmentation fault: EQUAL_D(1, std::strcmp("", NULL));
		EQUAL_D(-1, hare::strcmp(CHAR_PTR_NULL, ""));
		EQUAL_D( 1, hare::strcmp("", CHAR_PTR_NULL));
		EQUAL_D( 0, hare::strcmp(CHAR_PTR_NULL, CHAR_PTR_NULL));
	}

	static void test_memchr() {
		EQUAL_D(NULL, std::memchr(CHAR_PTR_NULL, 'x', 0));
		// Segmentation fault: EQUAL_D(NULL, std::memchr(CHAR_PTR_NULL, 'x', 1));
	}

	static void test_strcat() {
		// Segmentation fault: EQUAL_D(NULL, std::strcat(NULL, "test"));
		EQUAL_D(NULL, hare::strcat(NULL, "test"));
		char ach[9] = "xy";
		// Segmentation fault: EQUAL_D(NULL, std::strcat(ach, NULL));
		EQUAL_D(ach, hare::strcat(ach, NULL));
		EQUAL_S("xy", hare::strcat(ach, NULL));
		EQUAL_S("xyz", hare::strcat(ach, "z"));
	}

	static void test_strchr() {
		// Segmentation fault: EQUAL_D(NULL, std::strchr(CHAR_PTR_NULL, 't'));
		EQUAL_D(NULL, hare::strchr(CHAR_PTR_NULL, 't'));
		char ach[9] = "xy";
		EQUAL_D(ach + 1, hare::strchr(ach, 'y'));
		*hare::strchr(ach, 'y') = 'z';
		EQUAL_S("xz", ach);
	}

	static void test_strlen() {
		EQUAL_D(0, std::strlen(""));
		// Segmentation fault: EQUAL_D(0, std::strlen(NULL));
		EQUAL_D(0, hare::strlen(NULL));
	}

	static void test_strdup() {
		// Segmentation fault: EQUAL_D(0, ::strdup(CHAR_PTR_NULL));
		EQUAL_D(0, hare::strdup(CHAR_PTR_NULL));
		EQUAL_S("Invalid argument", strerror(errno));
	}

	static void test_strndup() {
		// Segmentation fault: EQUAL_D(0, ::strndup(CHAR_PTR_NULL, 1));
		EQUAL_S("", ::strndup(CHAR_PTR_NULL, 0));
		EQUAL_S("x", ::strndup("xyz", 1));
		EQUAL_S("xyz", ::strndup("xyz", 100));
		EQUAL_D(0, hare::strndup(CHAR_PTR_NULL, 1));
		EQUAL_S("Invalid argument", strerror(errno));
	}

	static void test_strspn() {
		EQUAL_D(4, std::strspn("hello", "leh"));
		// Segmentation fault: EQUAL_D(0, std::strspn(CHAR_PTR_NULL, "abc"));
		EQUAL_D(0, hare::strspn(CHAR_PTR_NULL, "abc"));
		// Segmentation fault: EQUAL_D(0, std::strspn("hello", CHAR_PTR_NULL));
		EQUAL_D(0, hare::strspn("hello", CHAR_PTR_NULL));
		EQUAL_D(0, std::strspn("hello", ""));
		EQUAL_D(0, hare::strspn("hello", ""));
	}

	static void test_strcspn() {
		EQUAL_D(2, std::strcspn("hello", "ol"));
		// Segmentation fault: EQUAL_D(0, std::strcspn(CHAR_PTR_NULL, "abc"));
		EQUAL_D(0, hare::strcspn(CHAR_PTR_NULL, "abc"));
		// Segmentation fault: EQUAL_D(0, std::strcspn("hello", CHAR_PTR_NULL));
		EQUAL_D(5, hare::strcspn("hello", CHAR_PTR_NULL));
		EQUAL_D(5, std::strcspn("hello", ""));
		EQUAL_D(5, hare::strcspn("hello", ""));
	}

	static void test_strstr() {
		// Segmentation fault: EQUAL_D(NULL, std::strstr(CHAR_PTR_NULL, "ll"));
		EQUAL_D(NULL, hare::strstr(CHAR_PTR_NULL, "ll"));
		char ach[9] = "hello";
		// Segmentation fault: EQUAL_D(NULL, std::strstr(ach, CHAR_PTR_NULL));
		EQUAL_D(NULL, hare::strstr(ach, CHAR_PTR_NULL));
		EQUAL_D(ach + 2, hare::strstr(ach, "ll"));
		*hare::strstr(ach, "ll") = 'e';
		EQUAL_S("heelo", ach);
	}

	static void test_between() {
		EQUAL_D(1, hare::between("inside",  "abc", "mno"));
		EQUAL_D(0, hare::between("outside", "abc", "mno"));
	}

	static void test() {
		test_strcmp();
		test_memchr();
		test_strcat();
		test_strchr();
		test_strlen();
		test_strdup();
		test_strndup();
		test_strspn();
		test_strcspn();
		test_strstr();
		test_between();
	}
};
