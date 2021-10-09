#include "test.h"

#include <hare/algorithm>	// sort
#include <hare/throws/dirent.h>
#include <hare/wrap/dirent.h>

#include <vector>

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
		// order is random so store it and order it afterwards
		std::vector<std::string> entries;
		const std::vector<const char*>  expected = {".", "..", "3lines.txt", "3lines_noeol.txt", "empty.txt", "readonly.txt"};
		struct dirent *entry = nullptr;
		for (size_t i = 0; i < expected.size(); ++i) {
			entry = hare::throws::readdir(dir);
			ASSERT(entry);
			entries.push_back(entry->d_name);
		}
		entry = hare::throws::readdir(dir);
		EQUAL_D(NULL, entry);
		entry = hare::throws::readdir(dir);
		EQUAL_D(NULL, entry);

		hare::sort(entries);
		for (size_t i = 0; i < expected.size(); ++i) {
			EQUAL_S(expected.at(i), entries.at(i));
		}
	}

	static void test_scandir() {
		try {
			struct dirent **namelist = NULL;
			int n = hare::throws::scandir("/not/existing", &namelist, NULL, NULL);
		} catch (const std::system_error& ex) {
			EQUAL_S("scandir(\"/not/existing\") failed: No such file or directory", ex.what());
		}
	}

	static void test() {
		test_closedir();
		test_opendir();
		test_readdir();
		test_scandir();
	}
};
