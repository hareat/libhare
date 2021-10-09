#ifndef HARE_THROWS_PWD_H
#define HARE_THROWS_PWD_H

#include <pwd.h>

/***************************************************************************
 * Throws an exception (derived of std::system_error) in case of any error.
 *
 * @author Hannes Reisinger github@HaRe.at
 ***************************************************************************/

#include <unistd.h>	// geteuid
#include <hare/system_error>

namespace hare {
	namespace throws {
		inline const char* whoami() {
			// If one wants to check errno after the call, it should be set to zero before the call.
			errno = 0;
			// getuid() and geteuid() are always successful.
			struct passwd *pwd = getpwuid(geteuid());
			if (pwd)
				return pwd->pw_name;
			else
				throw hare::system_error("%s() failed", __func__);
		}
	}	// namespace throws
}	// namespace hare

#endif	// HARE_THROWS_PWD_H
