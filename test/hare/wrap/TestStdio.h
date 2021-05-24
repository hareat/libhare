#include "test.h"

#include <hare/fcntl.h>
#include <hare/throws/cstdio>
#include <hare/wrap/cstdio>

struct TestHareWrapStdio {
	static void test_FILE() {
		hare::wrap::FILE emptyfp;
		ASSERT(emptyfp == NULL);

		const char *path = "tmp/TestHareWrapStdio.tmp";
		const char *data = "Testdata\n";
		int fd = 0;
		FILE *cfp = NULL;
		{
			hare::wrap::FILE fp(hare::throws::fopen(path, "w"));
			ASSERT(fp);
			hare::throws::fputs(data, fp);

			cfp = fp;
			fd = fileno(cfp);
			ASSERT(fd != EOF);	// we have a valid file handle
			ASSERT(hare::is_fd_open(fd));
		}	// automatically closes the file
		EQUAL_D(EOF, fileno(cfp));	// file handle is no longer available
		ASSERT(!hare::is_fd_open(fd));

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
