#include "hare/signal.h"
#include "hare/throws/signal.h"
#include "hare/signalsafe/writef"

#include <exception>
#include <cstdio>
#include <cstdlib>	// EXIT_*
#include <cstring>

namespace sigsaf = hare::signalsafe;


static int g_signum = 0;

static void my_signal_handler(int signum) {
	g_signum = signum;
	sigsaf::writef(2, "signal %d=%s caught\n", signum, sigsaf::signum_to_sz(signum));
}


struct TestHareSignal {
	static void test_itoa() {
		char ach[5] = "";
		EQUAL_S( "123", sigsaf::itoa(  123, ach, 10));
		EQUAL_S( "abc", sigsaf::itoa(0xABC, ach, 16));
		EQUAL_S("1234", sigsaf::itoa(01234, ach,  8));
		EQUAL_S( "111", sigsaf::itoa(    7, ach,  2));
		EQUAL_S("-123", sigsaf::itoa( -123, ach, 10));
		// buffer will be not big enough for the following
		EQUAL_S(    "", sigsaf::itoa(12345, ach, 10));
		EQUAL_S(    "", sigsaf::itoa(-1234, ach, 10));
	}

	static void test_signal() {
		hare::sighandler_restorer srUsr1(SIGUSR1, hare::throws::signal(SIGUSR1, my_signal_handler));
		hare::sighandler_restorer srUsr2(SIGUSR2, hare::throws::signal(SIGUSR2, my_signal_handler));
		hare::throws::raise(SIGUSR1);
		sleep(1);
		EQUAL_D(SIGUSR1, g_signum);
		hare::throws::raise(SIGUSR2);
		sleep(1);
		EQUAL_D(SIGUSR2, g_signum);
	}

	static void test() {
		test_itoa();
		test_signal();
	}
};
