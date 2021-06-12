#ifndef HARE_SIGNALSAFE_SIGNAL_H
#define HARE_SIGNALSAFE_SIGNAL_H

#include <signal.h>

/***************************************************************
 * hare/signalsafe/signal.h async-signal-safe functions of signal.h.
 * Only functions of the list in man signal-safety are allowed.
 *
 * @author Hannes Reisinger github@HaRe.at
 ***************************************************************/

namespace hare {
	namespace signalsafe {
		using ::kill;
		using ::pthread_kill;
		using ::pthread_self;
		using ::pthread_sigmask;
		using ::raise;
		using ::sigaction;
		using ::sigaddset;
		using ::sigdelset;
		using ::sigemptyset;
		using ::sigfillset;
		using ::sigismember;
		using ::signal;
		using ::sigpause;
		using ::sigpending;
		using ::sigprocmask;
		using ::sigqueue;
		using ::sigsuspend;
	}	// namespace signalsafe
}	// namespace hare

#endif	// HARE_SIGNALSAFE_SIGNAL_H
