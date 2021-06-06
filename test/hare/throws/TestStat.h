#include "test.h"

#include <hare/throws/stat.h>

struct TestHareThrowsStat {
	static void test_chmod() {
		EQUAL_D(-1, ::chmod(CHAR_PTR_NULL, 0));
		EQUAL_D(EFAULT, errno);	// bad address
		EQUAL_D(-1, ::chmod("/not/existing", 0));
		EQUAL_D(ENOENT, errno);	// No such file or directory

		try {
			hare::throws::chmod(CHAR_PTR_NULL, 0);
			FAIL("should not reach");
		} catch (const std::invalid_argument& ex) {
			EQUAL_S("chmod(path is NULL)", ex.what());
		}
		try {
			hare::throws::chmod("/not/existing", 0);
			FAIL("should not reach");
		} catch (const std::system_error& ex) {
			EQUAL_S("chmod(\"/not/existing\", 000) failed: No such file or directory", ex.what());
		}
		try {
			hare::throws::chmod("/", 0777);
			FAIL("should not reach - otherwise you have a real security problem on your system");
		} catch (const std::system_error& ex) {
			EQUAL_S("chmod(\"/\", 777) failed: Operation not permitted", ex.what());
		}
	}

	static void test_mkdir() {
		EQUAL_D(-1, ::mkdir(CHAR_PTR_NULL, 0));
		EQUAL_D(EFAULT, errno);	// bad address
		EQUAL_D(-1, ::mkdir("/not/existing/subdir", 0));
		EQUAL_D(ENOENT, errno);	// No such file or directory

		try {
			hare::throws::mkdir(CHAR_PTR_NULL, 0);
			FAIL("should not reach");
		} catch (const std::invalid_argument& ex) {
			EQUAL_S("mkdir(path is NULL)", ex.what());
		}
		try {
			hare::throws::mkdir("/not/existing/subdir", 0);
			FAIL("should not reach");
		} catch (const std::system_error& ex) {
			EQUAL_S("mkdir(\"/not/existing/subdir\", 000) failed: No such file or directory", ex.what());
		}
		try {
			hare::throws::mkdir("/notallowed", 0777);
			FAIL("should not reach - otherwise you have a real security problem on your system");
		} catch (const std::system_error& ex) {
			EQUAL_S("mkdir(\"/notallowed\", 777) failed: Permission denied", ex.what());
		}
	}

	static void test_stat() {
		struct stat* STAT_PTR_NULL = NULL;
		EQUAL_D(-1, ::stat(CHAR_PTR_NULL, STAT_PTR_NULL));
		EQUAL_D(EFAULT, errno);	// bad address
		EQUAL_D(-1, ::stat("/not/existing/subdir", STAT_PTR_NULL));
		EQUAL_D(ENOENT, errno);	// No such file or directory

		try {
			hare::throws::stat(CHAR_PTR_NULL, STAT_PTR_NULL);
			FAIL("should not reach");
		} catch (const std::invalid_argument& ex) {
			EQUAL_S("stat(path and statbuf are NULL)", ex.what());
		}
		struct stat statbuf;
		try {
			hare::throws::stat("/not/existing", &statbuf);
			FAIL("should not reach");
		} catch (const std::system_error& ex) {
			EQUAL_S("stat(\"/not/existing\") failed: No such file or directory", ex.what());
		}
	}

	static void test() {
		test_chmod();
		test_mkdir();
		test_stat();
	}
};
