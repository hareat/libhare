#include "hare/TestAlgorithm.h"
#include "hare/TestCstdio.h"
#include "hare/TestCstdlib.h"
#include "hare/TestCstring.h"
#include "hare/TestFunctional.h"
#include "hare/TestNumeric.h"
#include "hare/TestStrprintf.h"
#include "hare/throws/TestStdio.h"
#include "hare/wrap/TestStdio.h"

#include <exception>
#include <cstdio>
#include <cstdlib>	// EXIT_*

int main(const int argc, const char* argv[]) {
	try {
		TestHareAlgorithm::test();
		TestHareCstdio::test();
		TestHareCstdlib::test();
		TestHareCstring::test();
		TestHareFunctional::test();
		TestHareNumeric::test();
		TestHareStrprintf::test();
		TestHareThrowsStdio::test();
		TestHareWrapStdio::test();

		std::puts("All tests completed successfully");
		return EXIT_SUCCESS;
	} catch (const std::exception& ex) {
		std::fprintf(stderr, "%s() caught: %s\n", __func__, ex.what());
		return EXIT_FAILURE;
	}
}
