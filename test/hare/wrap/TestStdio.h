#include "test.h"

#include <hare/throws/stdio.h>
#include <hare/wrap/stdio.h>

struct TestHareWrapStdio {
	static void test_FILE() {
		hare::wrap::FILE emptyfp;
		ASSERT(emptyfp == NULL);

		const char *path = "tmp/TestHareWrapStdio.tmp";
		const char *data = "Testdata\n";
		FILE *cfp = NULL;
		{
			hare::wrap::FILE fp(hare::throws::fopen(path, "w"));
			ASSERT(fp);
			hare::throws::fputs(data, fp);

			cfp = fp;
			ASSERT(fileno(cfp) != EOF);	// now we have a file handle
		}	// automatically closes the file
		EQUAL_D(EOF, fileno(cfp));	// file handle is no longer available

		{
			hare::wrap::FILE fp(hare::throws::fopen(path, "r"));
			ASSERT(fp);
			char buffer[56] = {0};
			hare::throws::fgets(buffer, 56, fp);
			EQUAL_S(data, buffer);

			// compiler should prevent
			//hare::wrap::FILE fp2;
			//fp2 = fp;
		}
	}

	static void test() {
		test_FILE();
	}
};
