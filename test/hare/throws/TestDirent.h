#include "test.h"

#include <hare/throws/dirent.h>
#include <hare/wrap/dirent.h>

struct TestHareThrowsDirent {
	static void test_closedir() {
		try {
			hare::throws::closedir(NULL);
			FAIL("should not reach");
		} catch (const std::invalid_argument& ex) {
			EQUAL_S("closedir(dirp is NULL)", ex.what());
		}
	}

	static void test_opendir() {
		try {
			const hare::wrap::DIR dir(hare::throws::opendir("/not/existing"));
			FAIL("should not reach");
		} catch (const std::system_error& ex) {
			EQUAL_S("opendir(\"/not/existing\") failed: No such file or directory", ex.what());
		}
	}

	static void test_readdir() {
		try {
			hare::throws::readdir(NULL);
			FAIL("should not reach");
		} catch (const std::invalid_argument& ex) {
			EQUAL_S("readdir(dirp is NULL)", ex.what());
		}

		const hare::wrap::DIR dir(hare::throws::opendir("data"));
		// order is random
		struct dirent *entry = hare::throws::readdir(dir);
		EQUAL_S(".", entry->d_name);
		entry = hare::throws::readdir(dir);
		EQUAL_S("readonly.txt", entry->d_name);
		entry = hare::throws::readdir(dir);
		EQUAL_S("..", entry->d_name);
		entry = hare::throws::readdir(dir);
		EQUAL_D(NULL, entry);
		entry = hare::throws::readdir(dir);
		EQUAL_D(NULL, entry);
		entry = hare::throws::readdir(dir);
		EQUAL_D(NULL, entry);
	}

	static void test() {
		test_closedir();
		test_opendir();
		test_readdir();
	}
};
