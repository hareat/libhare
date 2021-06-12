#ifndef HARE_SIGNALSAFE_INET_H
#define HARE_SIGNALSAFE_INET_H

#include <arpa/inet.h>

/***************************************************************
 * hare/signalsafe/inet.h async-signal-safe functions of inet.h.
 * Only functions of the list in man signal-safety are allowed.
 *
 * @author Hannes Reisinger github@HaRe.at
 ***************************************************************/

namespace hare {
	namespace signalsafe {
		using ::htonl;
		using ::htons;
		using ::ntohl;
		using ::ntohs;
	}	// namespace signalsafe
}	// namespace hare

#endif	// HARE_SIGNALSAFE_INET_H
