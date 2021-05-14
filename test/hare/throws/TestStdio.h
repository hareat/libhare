#include "test.h"

#include <hare/throws/stdio.h>
#include <hare/wrap/stdio.h>

struct TestHareThrowsStdio {
	static void test_fclose() {
		try {
			hare::throws::fclose(NULL);
			FAIL("should not reach");
		} catch (const std::invalid_argument& ex) {
			EQUAL_S("fclose(stream is NULL)", ex.what());
		}
	}

	static void test_fdopen() {
		try {
			hare::throws::fdopen(0, NULL);
			FAIL("should not reach");
		} catch (const std::invalid_argument& ex) {
			EQUAL_S("fdopen(mode is NULL)", ex.what());
		}
	}

	static void test_fflush() {
		try {
			hare::throws::fflush(NULL);
			FAIL("should not reach");
		} catch (const std::invalid_argument& ex) {
			EQUAL_S("fflush(stream is NULL)", ex.what());
		}
	}

	static void test_fopen() {
		try {
			const hare::wrap::FILE fp(hare::throws::fopen("/not/existing", "r"));
			FAIL("should not reach");
		} catch (const std::system_error& ex) {
			EQUAL_S("fopen(\"/not/existing\", \"r\") failed: No such file or directory", ex.what());
		}

		try {
			const hare::wrap::FILE fp(hare::throws::fopen("data/readonly.txt", "w"));
			FAIL("should not reach");
		} catch (const std::system_error& ex) {
			EQUAL_S("fopen(\"data/readonly.txt\", \"w\") failed: Permission denied", ex.what());
		}
	}

	static void test_fputs() {
		try {
			hare::throws::fputs("data", NULL);
			FAIL("should not reach");
		} catch (const std::invalid_argument& ex) {
			EQUAL_S("fputs(stream is NULL)", ex.what());
		}

		const hare::wrap::FILE fp(hare::throws::fopen("data/readonly.txt", "r"));
		try {
			hare::throws::fputs(NULL, fp);
			FAIL("should not reach");
		} catch (const std::invalid_argument& ex) {
			EQUAL_S("fputs(data is NULL)", ex.what());
		}
		try {
			hare::throws::fputs("data", fp);
			FAIL("should not reach");
		} catch (const std::system_error& ex) {
			EQUAL_S("Bad file descriptor", ex.code().message());
			EQUAL_S("fputs(***) failed: Bad file descriptor", ex.what());
		}
	}

	static void test_tempnam() {
		ASSERT(hare::throws::tempnam(NULL, NULL));	// don't care about free
	}

	static void test_tmpnam() {
		ASSERT(hare::throws::tmpnam(NULL));
	}

	static void test_ungetc() {
		try {
			hare::throws::ungetc('c', NULL);
			FAIL("should not reach");
		} catch (const std::invalid_argument& ex) {
			EQUAL_S("ungetc(stream is NULL)", ex.what());
		}
	}

	static void test() {
		test_fclose();
		test_fdopen();
		test_fflush();
		test_fopen();
		test_fputs();
		test_tempnam();
		test_tmpnam();
		test_ungetc();
	}
};
