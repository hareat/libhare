#ifndef HARE_SIGNAL_H
#define HARE_SIGNAL_H

#include <signal.h>

/***************************************************************
 * hare/signal.h handy convenience methods for signal.h.
 *
 * @author Hannes Reisinger github@HaRe.at
 ***************************************************************/

namespace hare {
	inline const char* signum_to_sz(const int signum) {
		switch (signum) {
			case SIGABRT:
				return "SIGABRT";
			case SIGALRM:
				return "SIGALRM";
			case SIGBUS:
				return "SIGBUS";
			case SIGCHLD:
				return "SIGCHLD";
			case SIGCONT:
				return "SIGCONT";
			case SIGFPE:
				return "SIGFPE";
			case SIGHUP:
				return "SIGHUP";
			case SIGILL:
				return "SIGILL";
			case SIGINT:
				return "SIGINT";
			case SIGKILL:
				return "SIGKILL";
			case SIGPIPE:
				return "SIGPIPE";
			case SIGQUIT:
				return "SIGQUIT";
			case SIGSEGV:
				return "SIGSEGV";
			case SIGSTOP:
				return "SIGSTOP";
			case SIGTERM:
				return "SIGTERM";
			case SIGTSTP:
				return "SIGTSTP";
			case SIGTTIN:
				return "SIGTTIN";
			case SIGTTOU:
				return "SIGTTOU";
			case SIGUSR1:
				return "SIGUSR1";
			case SIGUSR2:
				return "SIGUSR2";
			case SIGPOLL:
				return "SIGPOLL";
			case SIGPROF:
				return "SIGPROF";
			case SIGSYS:
				return "SIGSYS";
			case SIGTRAP:
				return "SIGTRAP";
			case SIGURG:
				return "SIGURG";
			case SIGVTALRM:
				return "SIGVTALRM";
			case SIGXCPU:
				return "SIGXCPU";
			case SIGXFSZ:
				return "SIGXFSZ";
			default:
				return "unknown";
		}
	}
	namespace signalsafe {
		using hare::signum_to_sz;
	}	// namespace signalsafe

	// to automatically restore a signal handler to it's previous state.
	// Example: hare::sighandler_restorer srUsr1(SIGUSR1, ::signal(SIGUSR1, my_signal_handler);
	struct sighandler_restorer {
		sighandler_restorer(int _signum, sighandler_t _sighandler) : signum(_signum), sighandler(_sighandler) {}
		~sighandler_restorer() { if (sighandler != SIG_ERR) ::signal(signum, sighandler); }
		// public seems to be OK because they are const
		const int signum;
		const sighandler_t sighandler;
	};
}	// namespace hare

#endif	// HARE_SIGNAL_H
