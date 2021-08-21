#include "hare/TestAlgorithm.h"
#include "hare/TestCstdio.h"
#include "hare/TestCstdlib.h"
#include "hare/TestCstring.h"
#include "hare/TestFunctional.h"
#include "hare/TestLeakyBucket.h"
#include "hare/TestMacSz.h"
#include "hare/TestNumeric.h"
#include "hare/TestSignal.h"
#include "hare/TestStrprintf.h"
#include "hare/throws/TestCstdio.h"
#include "hare/throws/TestCstdlib.h"
#include "hare/throws/TestDirent.h"
#include "hare/throws/TestStat.h"
#include "hare/wrap/TestCstdio.h"
#include "hare/wrap/TestDirent.h"

#include <exception>
#include <cstdio>
#include <cstdlib>	// EXIT_*

// use this pointers to avoid warning: null argument where non-null required
char* const CHAR_PTR_NULL = NULL;

int main(const int argc, const char* argv[]) {
	try {
		TestHareAlgorithm::test();
		TestHareCstdio::test();
		TestHareCstdlib::test();
		TestHareCstring::test();
		TestHareFunctional::test();
		TestHareLeakyBucket::test();
		TestHareMacSz::test();
		TestHareNumeric::test();
		TestHareSignal::test();
		TestHareStrprintf::test();
		TestHareThrowsCstdio::test();
		TestHareThrowsCstdlib::test();
		TestHareThrowsDirent::test();
		TestHareThrowsStat::test();
		TestHareWrapCstdio::test();
		TestHareWrapDirent::test();

		std::puts("All tests completed successfully");
		return EXIT_SUCCESS;
	} catch (const hare::system_error& ex) {
		std::fprintf(stderr, "%s() caught: %s\n", __func__, ex.what());
		std::fflush(stderr);
		ex.backtrace_write(2);
		return EXIT_FAILURE;
	} catch (const std::exception& ex) {
		std::fprintf(stderr, "%s() caught: %s\n", __func__, ex.what());
		return EXIT_FAILURE;
	}
}
