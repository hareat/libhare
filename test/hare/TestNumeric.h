#include "test.h"

#include <hare/numeric>

#include <vector>

struct TestHareNumeric {
	static void test_accumulate() {
		const std::vector<int> vi = {1, 2, 3};
		EQUAL_D(6, hare::accumulate(vi, 0));
		const std::vector<std::string> vs = {"a", "bb", "ccc"};
		EQUAL_D(6, hare::accumulate(vs, 0, [](int i, const std::string& s) { return i + s.length(); }));
	}

	static void test_iota() {
		std::vector<int> vi(3);  // 0, 0, 0
		EQUAL_D(0, vi.back());
		hare::iota(vi, 1);       // 1, 2, 3
		EQUAL_D(1, vi.front());
		EQUAL_D(3, vi.back());
	}

	static void test() {
		test_accumulate();
		test_iota();
	}
};
