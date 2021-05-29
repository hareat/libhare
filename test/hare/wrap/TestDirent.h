#include "test.h"

#include <hare/throws/dirent.h>
#include <hare/wrap/dirent.h>

#include <hare/algorithm>

inline int is_file(const struct dirent *entry) {
	return entry->d_type == DT_REG;
}

inline int is_directory(const struct dirent *entry) {
	return entry->d_type == DT_DIR;
}

struct TestHareWrapDirent {
	static void test_ScandirNamelist() {
		hare::wrap::ScandirNamelist namelist("data", NULL, alphasort);
		struct dirent** itor = namelist.begin();
		EQUAL_S(".", (*itor++)->d_name);
		EQUAL_S("..", (*itor++)->d_name);
		EQUAL_S("readonly.txt", (*itor++)->d_name);
		ASSERT(itor == namelist.end());

		namelist.scandir("data", is_file, NULL);
		itor = namelist.begin();
		EQUAL_S("readonly.txt", (*itor++)->d_name);
		ASSERT(itor == namelist.end());
		for (struct dirent *entry : namelist)
			EQUAL_S("readonly.txt", entry->d_name);
		hare::for_each(namelist, [](struct dirent *entry) { EQUAL_S("readonly.txt", entry->d_name); });
		std::for_each(namelist.begin(), namelist.end(), [](struct dirent *entry) { EQUAL_S("readonly.txt", entry->d_name); });

		namelist.scandir("data", is_directory, alphasort);
		itor = namelist.begin();
		EQUAL_S(".", (*itor++)->d_name);
		EQUAL_S("..", (*itor++)->d_name);
		ASSERT(itor == namelist.end());
	}

	static void test() {
		test_ScandirNamelist();
	}
};
