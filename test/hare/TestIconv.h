#include "test.h"

#include <hare/iconv.h>

struct TestHareIconv {
	static void test_iconv() {
		const std::string utf8 = "abc\u00F6", iso88591 = "abc\xF6";	// &ouml;
		const hare::Iconv utf8_to_iso88591("ISO-8859-1", "UTF-8", 1);
		const hare::Iconv iso88591_to_utf8("UTF-8", "ISO-8859-1", 4);
		EQUAL_S(utf8, iso88591_to_utf8(iso88591));
		EQUAL_S(iso88591, utf8_to_iso88591(utf8));

		try {
			utf8_to_iso88591("\u0110");	// D with Stroke
			FAIL("should not reach");
		} catch (const hare::system_error& ex) {
			EQUAL_S("UTF-8 to ISO-8859-1 failed: Invalid or incomplete multibyte or wide character", ex.what());
		}
	}

	static void test() {
		test_iconv();
	}
};
