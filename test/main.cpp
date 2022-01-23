#include "hare/TestAlgorithm.h"
#include "hare/TestCstdio.h"
#include "hare/TestCstdlib.h"
#include "hare/TestCstring.h"
#include "hare/TestFstream.h"
#include "hare/TestFunctional.h"
#include "hare/TestIconv.h"
#include "hare/TestLeakyBucket.h"
#include "hare/TestMacSz.h"
#include "hare/TestMemory.h"
#include "hare/TestNumeric.h"
#include "hare/TestPwd.h"
#include "hare/TestSignal.h"
#include "hare/TestStrprintf.h"
#include "hare/throws/TestCstdio.h"
#include "hare/throws/TestCstdlib.h"
#include "hare/throws/TestCurl.h"
#include "hare/throws/TestDirent.h"
#include "hare/throws/TestIconv.h"
#include "hare/throws/TestStat.h"
#include "hare/wrap/TestCstdio.h"
#include "hare/wrap/TestCstdlib.h"
#include "hare/wrap/TestDirent.h"

#include <exception>
#include <cstdio>
#include <cstdlib>	// EXIT_*
#include <cxxabi.h>

// use this pointers to avoid warning: null argument where non-null required
char* const CHAR_PTR_NULL = NULL;

std::string demangle(const char *mangled_name) {
	int status = -9;	// 0 means success. -1, -2, -3 are declared failures.
	hare::wrap::auto_free<char> result(abi::__cxa_demangle(mangled_name, NULL, NULL, &status));
	return (status == 0) ? result.get() : mangled_name;
}

int main(const int argc, const char* argv[]) {
	try {
		TestHareAlgorithm::test();
		TestHareCstdio::test();
		TestHareCstdlib::test();
		TestHareCstring::test();
		TestHareFstream::test();
		TestHareFunctional::test();
		TestHareIconv::test();
		TestHareLeakyBucket::test();
		TestHareMacSz::test();
		TestHareMemory::test();
		TestHareNumeric::test();
		TestHarePwd::test();
		TestHareSignal::test();
		TestHareStrprintf::test();
		TestHareThrowsCstdio::test();
		TestHareThrowsCstdlib::test();
		TestHareThrowsCurl::test();
		TestHareThrowsDirent::test();
		TestHareThrowsIconv::test();
		TestHareThrowsStat::test();
		TestHareWrapCstdio::test();
		TestHareWrapCstdlib::test();
		TestHareWrapDirent::test();

		std::puts("All tests completed successfully");
		return EXIT_SUCCESS;
	} catch (const std::exception& ex) {
		std::fprintf(stderr, "%s() caught exception %s: %s\n",
			__func__, demangle(typeid(ex).name()).c_str(), ex.what());
		std::fflush(stderr);
		auto bt = dynamic_cast<const hare::backtrace *>(&ex);
		if (bt)
			bt->backtrace_addr2line_fd(2);
	}
	return EXIT_FAILURE;
}
