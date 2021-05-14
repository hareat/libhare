#include "hare/TestStrprintf.h"
#include "hare/throws/TestStdio.h"
#include "hare/wrap/TestStdio.h"

#include <exception>
#include <stdio.h>
#include <stdlib.h>	// EXIT_*

int main(const int argc, const char* argv[]) {
	try {
		TestHareStrprintf::test();
		TestHareThrowsStdio::test();
		TestHareWrapStdio::test();

		puts("All tests completed successfully");
		return EXIT_SUCCESS;
	} catch (const std::exception& ex) {
		fprintf(stderr, "%s() caught: %s\n", __func__, ex.what());
		return EXIT_FAILURE;
	}
}
