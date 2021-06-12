#ifndef HARE_SIGNALSAFE_SOCKET_H
#define HARE_SIGNALSAFE_SOCKET_H

#include <sys/socket.h>

/***************************************************************
 * hare/signalsafe/socket.h async-signal-safe functions of socket.h.
 * Only functions of the list in man signal-safety are allowed.
 *
 * @author Hannes Reisinger github@HaRe.at
 ***************************************************************/

namespace hare {
	namespace signalsafe {
		using ::accept;
		using ::bind;
		using ::connect;
		using ::getpeername;
		using ::getsockname;
		using ::getsockopt;
		using ::listen;
		using ::recv;
		using ::recvfrom;
		using ::recvmsg;
		using ::send;
		using ::sendmsg;
		using ::sendto;
		using ::setsockopt;
		using ::shutdown;
		using ::sockatmark;
		using ::socket;
		using ::socketpair;

	}	// namespace signalsafe
}	// namespace hare

#endif	// HARE_SIGNALSAFE_SOCKET_H
