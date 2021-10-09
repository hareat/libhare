#include "test.h"

#include <hare/fstream>
#include <hare/throws/unistd.h>	// unlink

struct TestHareFstream {
	static void test_read() {
		EQUAL_S("this file is read only\n", hare::fstream::read("data/readonly.txt"));
		EQUAL_S("", hare::fstream::read("data/empty.txt"));
	}

	static void test_head() {
		EQUAL_S("line 1\nline 2\nline 3\n", hare::fstream::head("data/3lines.txt"));
		EQUAL_S("line 1\nline 2\n", hare::fstream::head("data/3lines.txt", 2));
		EQUAL_S("", hare::fstream::head("data/empty.txt"));
	}

	static void test_tail() {
		EQUAL_S("line 1\nline 2\nline 3\n", hare::fstream::tail("data/3lines.txt"));
		EQUAL_S("line 2\nline 3\n", hare::fstream::tail("data/3lines.txt", 2));
		EQUAL_S("line 1\nline 2\nline 3", hare::fstream::tail("data/3lines_noeol.txt"));
		EQUAL_S("line 2\nline 3", hare::fstream::tail("data/3lines_noeol.txt", 2));
		EQUAL_S("", hare::fstream::tail("data/empty.txt"));
	}

	static void test_write() {
		const std::string content("hare fstream test write\n"), path("/tmp/harefstreamtestwrite.txt");
		hare::fstream::write(path, content);
		EQUAL_S(content, hare::fstream::read(path));
		hare::throws::unlink(path);
	}

	static void test() {
		test_read();
		test_head();
		test_tail();
		test_write();
	}
};
