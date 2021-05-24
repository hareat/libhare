#ifndef HARE_THROWS_UNISTD_H
#define HARE_THROWS_UNISTD_H

#include <unistd.h>

/***************************************************************************
 * Throws an exception (derived of std::system_error) in case of any error.
 *
 * (1) Many functions return 0 on sucess and return -1 in case of an error
 *     and set errno to indicate the error.
 *
 * @author Hannes Reisinger github@HaRe.at
 ***************************************************************************/

#include <hare/stdexcept>	// CHECK_NOT_NULL_ARG
#include <hare/system_error>

namespace hare {
	namespace throws {
		inline void chown(const char *path, uid_t owner, gid_t group) {
			CHECK_NOT_NULL_ARG1(path);
			if (::chown(path, owner, group) == -1)	// see (1)
				throw hare::system_error("%s('%s', %d, %d) failed", __func__, path, owner, group);
		}
		inline void chown(const std::string& path, uid_t owner, gid_t group) { chown(path.c_str(), owner, group); }

		inline void chown(const char *path, uid_t owner) {
			CHECK_NOT_NULL_ARG1(path);
			if (::chown(path, owner, -1) == -1)	// see (1)
				throw hare::system_error("%s('%s', %d) failed", __func__, path, owner);
		}
		inline void chown(const std::string& path, uid_t owner) { chown(path.c_str(), owner); }

		inline void chgrp(const char *path, gid_t group) {
			CHECK_NOT_NULL_ARG1(path);
			if (::chown(path, -1, group) == -1)	// see (1)
				throw hare::system_error("%s('%s', %d) failed", __func__, path, group);
		}
		inline void chgrp(const std::string& path, gid_t group) { chgrp(path.c_str(), group); }

		inline void close(int fd) {
			if (::close(fd) == -1)	// see (1)
				throw hare::system_error("%s() failed", __func__);
		}
	}	// namespace throws
}	// namespace hare

#endif	// HARE_THROWS_UNISTD_H
