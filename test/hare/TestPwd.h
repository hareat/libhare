#include "test.h"

#include <hare/pwd.h>

struct TestHarePwd {
	static void test_whoami() {
		EQUAL_S(getenv("USER"), hare::whoami());
	}

	static void test() {
		test_whoami();
	}
};
