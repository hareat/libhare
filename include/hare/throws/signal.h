#ifndef HARE_THROWS_SIGNAL_H
#define HARE_THROWS_SIGNAL_H

#include <signal.h>

/***************************************************************************
 * Throws an exception (derived of std::system_error) in case of any error.
 *
 * (1) returns zero on success, or -1 if an error occurs.
 *
 * (2) returns zero on success, or nonzero if an error occurs.
 *
 * @author Hannes Reisinger github@HaRe.at
 ***************************************************************************/

#include <hare/system_error>

namespace hare {
	namespace throws {
		inline void kill(pid_t pid, int sig) {
			if (::kill(pid, sig) != 0)	// see (1)
				throw hare::system_error("%s(%d, %d) failed", __func__, pid, sig);
		}

		inline void raise(int sig) {
			if (::raise(sig) != 0)	// see (2)
				throw hare::system_error("%s(%d) failed", __func__, sig);
		}

		inline sighandler_t signal(int signum, sighandler_t handler) {
			//  Note: handler NULL is a valid argument
			sighandler_t result = ::signal(signum, handler);
			if (result == SIG_ERR)
				throw hare::system_error("%s(%d) failed", __func__, signum);
			return result;
		}
	}	// namespace throws
}	// namespace hare

#endif	// HARE_THROWS_SIGNAL_H
