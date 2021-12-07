#include "test.h"

#include <hare/memory>

#include <vector>

struct TestHareMemory {
	static void test_owner_equal_to() {
		// different pointers but same content
		auto i1 = std::make_shared<int>(42), i2 = std::make_shared<int>(42);
		ASSERT(!(i1 == i2));
		ASSERT(hare::owner_equal_to<int>()(i1, i2));
		std::vector<std::shared_ptr<int>> vi = {i1, i2};
		hare::unique(vi);	// the pointers differ
		EQUAL_D(2, vi.size());
		hare::unique(vi, hare::owner_equal_to<int>());	// but the content is the same
		EQUAL_D(1, vi.size());
	}

	static void test() {
		test_owner_equal_to();
	}
};
