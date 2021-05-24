#include "test.h"

#include <hare/cstdio>

struct TestHareCstdio {
	static void test_snprintf() {
		char buffer[5];
		EQUAL_D(2, hare::snprintf(buffer, "%d", 12));
		EQUAL_S("12", buffer);
		EQUAL_D(9, hare::snprintf(buffer, "%d", 123456789));
		EQUAL_S("1234", buffer);
	}

	static void test() {
		test_snprintf();
	}
};
