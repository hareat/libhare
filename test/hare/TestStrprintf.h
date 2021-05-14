#include "test.h"

#include <hare/strprintf>

struct TestHareStrprintf {
	static void test_strprintf() {
		EQUAL_S("123456789", hare::strprintf("123%s", "456789"));
		EQUAL_S("123456", hare::strprintf<7>("123%s", "456789"));
		hare::strprintf(NULL);
	}

	static void test() {
		test_strprintf();
	}
};
