#ifndef HARE_FCNTL_H
#define HARE_FCNTL_H

#include <fcntl.h>

/***************************************************************
 * hare/fcntl.h handy convenience methods for fcntl.h.
 *
 * @author Hannes Reisinger github@HaRe.at
 ***************************************************************/

namespace hare {
	inline bool is_fd_open(int fd) {
		return ::fcntl(fd, F_GETFD) != -1 || errno != EBADF;
	}
}	// namespace hare

#endif	// HARE_FCNTL_H
