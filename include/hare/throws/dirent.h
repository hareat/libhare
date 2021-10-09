#ifndef HARE_THROWS_DIRENT_H
#define HARE_THROWS_DIRENT_H

#include <dirent.h>

/***************************************************************************
 * Throws an exception (derived of std::system_error) in case of any error.
 *
 * (1) Many functions return 0 on sucess and return -1 in case of an error
 *     and set errno to indicate the error.
 *
 * (2) Other functions return NULL in case of an error and set errno
 *     to indicate the error.
 *
 * @author Hannes Reisinger github@HaRe.at
 **************************************************************************/

#include <hare/stdexcept>	// CHECK_NOT_NULL_ARG
#include <hare/system_error>

namespace hare {
	namespace throws {
		inline void closedir(DIR *dirp) {
			CHECK_NOT_NULL_ARG1(dirp);
			if (::closedir(dirp) == -1)		// see (1)
				throw hare::system_error("%s() failed", __func__);
		}

		// returns a file descriptor (a nonnegative integer).
		// On error, -1 is returned, and errno is set to indicate the error.
		inline int dirfd(DIR *dirp) {
			CHECK_NOT_NULL_ARG1(dirp);
			int const result = ::dirfd(dirp);
			if (result == -1)
				throw hare::system_error("%s() failed", __func__);
			return result;
		}

		inline DIR* opendir(const char *name) {
			CHECK_NOT_NULL_ARG1(name);
			DIR * const result = ::opendir(name);
			if (result == NULL)		// see (2)
				throw hare::system_error("%s(\"%s\") failed", __func__, name);
			return result;
		}
		inline DIR* fdopendir(int fd) {
			DIR * const result = ::fdopendir(fd);
			if (result == NULL)		// see (2)
				throw hare::system_error("%s() failed", __func__);
			return result;
		}

		// @see man readdir
		// On success, readdir() returns a pointer to a dirent structure.
		// This structure may be statically allocated; do not attempt to free it.
		// If the end of the directory stream is reached, NULL is returned and
		// errno is not changed.
		// If an error occurs, NULL is returned and errno is set appropriately.
		// To distinguish end of stream and from an error, set errno to zero before
		// calling readdir() and then check the value of errno if NULL is returned.
		inline struct dirent* readdir(DIR *dirp) {
			CHECK_NOT_NULL_ARG1(dirp);
			errno = 0;
			struct dirent * const result = ::readdir(dirp);
			if (result == NULL && errno != 0)
				throw hare::system_error("%s() failed", __func__);
			return result;
		}

		// returns the number of directory entries selected.
		// On error, -1 is returned, with errno set to indicate the error.
		inline int scandir(const char *dir,
                   struct dirent ***namelist,
                   int (*filter)(const struct dirent *),
                   int (*compar)(const struct dirent **,
                                 const struct dirent **)) {
			CHECK_NOT_NULL_ARG1(dir);
			int const result = ::scandir(dir, namelist, filter, compar);
			if (result == -1)
				throw hare::system_error("%s(\"%s\") failed", __func__, dir);
			return result;
		}

		// returns the current location in the directory stream.
		// On error, -1 is returned, and errno is set to indicate the error.
		inline long telldir(DIR *dirp) {
			CHECK_NOT_NULL_ARG1(dirp);
			long const result = ::telldir(dirp);
			if (result == -1)
				throw hare::system_error("%s() failed", __func__);
			return result;
		}
	}	// namespace throws
}	// namespace hare

#endif	// HARE_THROWS_DIRENT_H
