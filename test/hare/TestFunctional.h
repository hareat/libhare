#include "test.h"

#include <hare/functional>

#ifdef USE_BOOST
#include <boost/algorithm/string/compare.hpp>
#endif	// USE_BOOST

#include <string>

struct TestHareFunctional {
	static void test_int() {
		ASSERT(std::less<int>()(1, 2));

#ifdef USE_BOOST
		ASSERT(boost::is_less()(1, 2));
#endif	// USE_BOOST

		ASSERT(hare::less()(1, 2));
	}

	static void test_str() {
		const std::string b = "b", a = "a", a2 = "a";
		ASSERT(std::less<const std::string>()(a, b));
		ASSERT(std::greater<const std::string>()(b, a));

#ifdef USE_BOOST
		ASSERT(boost::is_less()(a, b));
		ASSERT(boost::is_equal()(a, a2));
#endif	// USE_BOOST

		ASSERT(hare::less()(a, b));
		ASSERT(hare::equal_to()(a, a2));
	}

	static void test_sz() {
		// use variables to ensure that b has a lower address than a
		const char b[] = "b", a[] = "a", a2[] = "a";
		//ASSERT(std::less<const char*>()(a, b));
		//ASSERT(std::greater<const char*>()(b, a));

#ifdef USE_BOOST
		// also boost is not handling char* in the way I would assume
//		ASSERT(boost::is_less()(a, b));
//		ASSERT(boost::is_equal()(a, a2));
#endif	// USE_BOOST

		ASSERT(hare::less()(a, b));
		ASSERT(hare::equal_to()(a, a2));
	}

	static void test() {
		test_int();
		test_str();
		test_sz();
	}
};
