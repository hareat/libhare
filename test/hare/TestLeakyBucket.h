#include "test.h"

#include <hare/leaky_bucket.h>

#include <time.h>	// time
#include <unistd.h>	// sleep

struct my_time_functor {
	typedef	time_t result_type;
	result_type operator()() const { return time(NULL); }
};

struct TestHareLeakyBucket {
	static void test_rain_barrel() {
		hare::leaky_bucket<> rain_barrel(100, 1);	// 100l leaks 1l per day
		EQUAL_D(0, rain_barrel.level());
		EQUAL_D(0, rain_barrel.elapsed(1).pour(60));	// first rainy day
		EQUAL_D(60, rain_barrel.level());
		EQUAL_D(19, rain_barrel.elapsed(1).pour(60));	// second rainy day
		EQUAL_D(100, rain_barrel.level());
		EQUAL_D(93, rain_barrel.elapsed(7).level());	// sunny week
	}

	static void test_bandwith_limit() {
		// 4KBit per second and too small buffer with just 8KBit or 1KByte
		hare::leaky_bucket_t<my_time_functor> download(8000, 4000);
		EQUAL_D(0, download.level());
		EQUAL_D(0, download.pour(1000 * 8));	// first KByte
		EQUAL_D(8000, download.level());
		sleep(1);
		EQUAL_D(4000, download.pour(1000 * 8));	// second KByte arrives one second later
		// compiler has to forbid this: download.elapsed(100);
	}

	static void test() {
		test_rain_barrel();
		test_bandwith_limit();
	}
};
