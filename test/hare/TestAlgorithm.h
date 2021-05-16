#include "test.h"

#include <hare/algorithm>

#include <vector>

struct TestHareAlgorithm {
	static void test_unique() {
		std::vector<int> vi = {1, 1, 1, 2, 2, 2, 3, 3, 3};
		EQUAL_D(9, vi.size());
		ASSERT(hare::unique(vi));
		EQUAL_D(3, vi.size());
		EQUAL_D(1, vi.front());
		EQUAL_D(3, vi.back());
	}

	static void test() {
		test_unique();
	}
};
