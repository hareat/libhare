#ifndef HARE_THROWS_STAT_H
#define HARE_THROWS_STAT_H

#include <sys/stat.h>

/***************************************************************************
 * Throws an exception (derived of std::system_error) in case of any error.
 *
 * (1) Many functions return 0 on sucess and return -1 in case of an error
 *     and set errno to indicate the error.
 *
 * @author Hannes Reisinger github@HaRe.at
 ***************************************************************************/

#include <hare/system_error>

namespace hare {
	namespace throws {
		inline void chmod(const char *path, mode_t mode) {
			CHECK_NOT_NULL_ARG1(path);
			if (::chmod(path, mode) != 0)		// see (1)
				throw hare::system_error("%s(\"%s\", %03o) failed", __func__, path, mode);
		}
		inline void chmod(const std::string& path, mode_t mode) { chmod(path.c_str(), mode); }

		inline void fchmod(int fd, mode_t mode) {
			if (::fchmod(fd, mode) != 0)		// see (1)
				throw hare::system_error("%s(%d, %03o) failed", __func__, fd, mode);
		}

		inline void mkdir(const char *path, mode_t mode) {
			CHECK_NOT_NULL_ARG1(path);
			if (::mkdir(path, mode) != 0)		// see (1)
				throw hare::system_error("%s(\"%s\", %03o) failed", __func__, path, mode);
		}
		inline void mkdir(const std::string& path, mode_t mode) { mkdir(path.c_str(), mode); }

		inline void mkfifo(const char *path, mode_t mode) {
			CHECK_NOT_NULL_ARG1(path);
			if (::mkfifo(path, mode) != 0)		// see (1)
				throw hare::system_error("%s(\"%s\", %03o) failed", __func__, path, mode);
		}
		inline void mkfifo(const std::string& path, mode_t mode) { mkfifo(path.c_str(), mode); }

		inline void mknod(const char *path, mode_t mode, dev_t dev) {
			CHECK_NOT_NULL_ARG1(path);
			if (::mknod(path, mode, dev) != 0)		// see (1)
				throw hare::system_error("%s(\"%s\", %03o, %d) failed", __func__, path, mode, dev);
		}
		inline void mknod(const std::string& path, mode_t mode, dev_t dev) { mknod(path.c_str(), mode, dev); }

		inline void stat(const char *path, struct stat *statbuf) {
			CHECK_NOT_NULL_ARG2(path, statbuf);
			if (::stat(path, statbuf) != 0)		// see (1)
				throw hare::system_error("%s(\"%s\") failed", __func__, path);
		}

		inline void fstat(int fd, struct stat *statbuf) {
			CHECK_NOT_NULL_ARG1(statbuf);
			if (::fstat(fd, statbuf) != 0)		// see (1)
				throw hare::system_error("%s(%d) failed", __func__, fd);
		}
	}	// namespace throws
}	// namespace hare

#endif	// HARE_THROWS_STAT_H
