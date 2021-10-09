#ifndef HARE_PWD_H
#define HARE_PWD_H

#include <pwd.h>

/***************************************************************
 * hare/pwd.h handy convenience methods for pwd.h.
 *
 * @author Hannes Reisinger github@HaRe.at
 ***************************************************************/

#include <unistd.h>	// geteuid

namespace hare {
	inline const char* whoami() {
		// getuid() and geteuid() are always successful.
		struct passwd *pwd = getpwuid(geteuid());
		return pwd ? pwd->pw_name : nullptr;
	}
}	// namespace hare

#endif	// HARE_PWD_H
