#include "test.h"

#include <hare/cstdlib>

struct TestHareCstdlib {
	static void test_atof() {
		EQUAL_F(123.1, hare::atof("123.1"));
		EQUAL_F(123.1, hare::atof("  +123.1xyz"));
		EQUAL_F(  0.0, hare::atof(""));
		// Segmentation fault: EQUAL_F(0.0, std::atof(NULL));
		EQUAL_F(  0.0, hare::atof(NULL));
		EQUAL_F(  0.0, hare::atof("not a number"));
	}

	static void test_atoi() {
		EQUAL_D(123, hare::atoi("123"));
		EQUAL_D(123, hare::atoi("  +123xyz"));
		EQUAL_D(  0, hare::atoi(""));
		// Segmentation fault: EQUAL_D(0, std::atoi(NULL));
		EQUAL_D(  0, hare::atoi(NULL));
		EQUAL_D(  0, hare::atoi("not a number"));
	}

	static void test_getenv() {
		EQUAL_D(NULL, std::getenv("not in environment"));
		// Segmentation fault: EQUAL_D(NULL, std::getenv(NULL));
		EQUAL_D(NULL, hare::getenv(NULL));
	}

	static void test_strtod() {
		EQUAL_F(123.1, hare::strtod("  +123.1xyz", NULL));
		// Segmentation fault: EQUAL_F(0.0, std::strtod(NULL, NULL));
		EQUAL_F(  0.0, hare::strtod(NULL, NULL));
		EQUAL_F(  0.0, hare::strtod("not a number", NULL));
	}

	static void test_strtol() {
		EQUAL_D(123, hare::strtol("  +123.1xyz", NULL, 10));
		// Segmentation fault: EQUAL_D(0, std::strtol(NULL, NULL, 10));
		EQUAL_D(  0, hare::strtol(NULL, NULL, 10));
		EQUAL_D(  0, hare::strtol("not a number", NULL, 10));
	}

	static void test_system() {
		EQUAL_D(EXIT_FAILURE, std::system(NULL));
	}

	static void test() {
		test_atof();
		test_atoi();
		test_getenv();
		test_strtod();
		test_strtol();
		test_system();
	}
};
