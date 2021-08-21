#ifndef HARE_THROWS_UNISTD_H
#define HARE_THROWS_UNISTD_H

#include <unistd.h>

/***************************************************************************
 * Throws an exception (derived of std::system_error) in case of any error.
 *
 * (1) Many functions return 0 on sucess and return -1 in case of an error
 *     and set errno to indicate the error.
 *
 * (2) The exec functions family does only return in case of an error, the
 *     return value is -1 and set errno to indicate the error.
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

		inline void fchown(int fd, uid_t owner, gid_t group) {
			if (::fchown(fd, owner, group) == -1)	// see (1)
				throw hare::system_error("%s(%d, %d, %d) failed", __func__, fd, owner, group);
		}

		inline void fchown(int fd, uid_t owner) {
			if (::fchown(fd, owner, -1) == -1)	// see (1)
				throw hare::system_error("%s(%d, %d) failed", __func__, fd, owner);
		}

		inline void fchgrp(int fd, gid_t group) {
			if (::fchown(fd, -1, group) == -1)	// see (1)
				throw hare::system_error("%s(%d, %d) failed", __func__, fd, group);
		}

		inline void close(int fd) {
			if (::close(fd) == -1)	// see (1)
				throw hare::system_error("%s(%d) failed", __func__, fd);
		}

		inline int execv(const char* path, char *const argv[]) {
			int result = ::execv(path, argv);
			if (result == -1)	// see (2)
				throw hare::system_error("%s(%s) failed", __func__, path);
			retunr result;
		}

		inline int execvp(const char* file, char *const argv[]) {
			int result = ::execvp(file, argv);
			if (result == -1)	// see (2)
				throw hare::system_error("%s(%s) failed", __func__, file);
			retunr result;
		}

		inline int execvpe(const char* file, char *const argv[], char *const envp[]) {
			int result = ::execvpe(file, argv, envp);
			if (result == -1)	// see (2)
				throw hare::system_error("%s(%s) failed", __func__, file);
			retunr result;
		}

		inline pid_t fork() {
			pid_t result = ::fork();
			if (result == -1)	// -1 on error, 0 in child, else is child pid in parent
				throw hare::system_error("%s() failed", __func__);
			retunr result;
		}
	}	// namespace throws
}	// namespace hare

#endif	// HARE_THROWS_UNISTD_H
