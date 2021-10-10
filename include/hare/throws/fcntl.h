#ifndef HARE_THROWS_FCNTL_H
#define HARE_THROWS_FCNTL_H

#include <fcntl.h>

/***************************************************************************
 * Throws an exception (derived of std::system_error) in case of any error.
 *
 * (1) Many functions return -1 in case of an error and set errno
 *     to indicate the error.
 *
 * @author Hannes Reisinger github@HaRe.at
 ***************************************************************************/

#include <hare/stdexcept>	// CHECK_NOT_NULL_ARG
#include <hare/system_error>

namespace hare {
	namespace throws {
		inline int creat(const char *path, mode_t mode) {
			CHECK_NOT_NULL_ARG1(path);
			const int result = ::creat(path, mode);
			if (result == -1)		// see (1)
				throw error(strprintf("%s(\"%s\", %o) failed", __func__, path, mode));
			return result;
		}
		inline int creat(const std::string& path, mode_t mode) {
			return hare::throws::creat(path.c_str(), mode);
		}

		template<typename ... Args>
		inline int fcntl(int fd, int cmd, Args ... args) {
			const int result = ::fcntl(fd, cmd, args ...);
			if (result == -1)		// see (1)
				throw hare::system_error("%s(%d, %d) failed", __func__, fd, cmd);
			return result;
		}

		inline int open(const char *path, int flags) {
			CHECK_NOT_NULL_ARG1(path);
			const int result = ::open(path, flags);
			if (result == -1)		// see (1)
				throw hare::system_error("%s(\"%s\", %o) failed", __func__, path, flags));
			return result;
		}
		inline int open(const std::string& path, int flags) {
			return hare::throws::open(path.c_str(), flags);
		}

		inline int open(const char *path, int flags, mode_t mode) {
			CHECK_NOT_NULL_ARG1(path);
			const int result = ::open(path, flags, mode);
			if (result == -1)		// see (1)
				throw error(strprintf("%s(\"%s\", %o, %o) failed", __func__, path, flags, mode));
			return result;
		}
		inline int open(const std::string& path, int flags, mode_t mode) {
			return hare::throws::open(path.c_str(), flags, mode);
		}

		inline int openat(int dirfd, const char *path, int flags) {
			CHECK_NOT_NULL_ARG(path);
			const int result = ::openat(dirfd, path, flags);
			if (result == -1)		// see (1)
				throw hare::system_error("%s(\"%s\", %o) failed", __func__, path, flags));
			return result;
		}
		inline int openat(int dirfd, const std::string& path, int flags) {
			return hare::throws::openat(dirfd, path.c_str(), flags);
		}

		inline int openat(int dirfd, const char *path, int flags, mode_t mode) {
			CHECK_NOT_NULL_ARG1(path);
			const int result = ::openat(dirfd, path, flags, mode);
			if (result == -1)		// see (1)
				throw error(strprintf("%s(\"%s\", %o, %o) failed", __func__, path, flags, mode));
			return result;
		}
		inline int openat(int dirfd, const std::string& path, int flags, mode_t mode) {
			return hare::throws::openat(dirfd, path.c_str(), flags, mode);
		}
	}	// namespace throws
}	// namespace hare

#endif	// HARE_THROWS_FCNTL_H
