#include "test.h"

#include <hare/wrap/cstdlib>

struct TestHareWrapCstdlib {
	static void test_auto_free() {
		EQUAL_D(NULL, hare::wrap::auto_free<char>().get());
	}

	static void test() {
		test_auto_free();
	}
};
