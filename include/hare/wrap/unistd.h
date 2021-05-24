#ifndef HARE_UNISTD_H
#define HARE_UNISTD_H

#include <unistd.h>

/***************************************************************
 * hare/unistd.h some convenience helper for unistd.h.
 *
 * @author Hannes Reisinger github@HaRe.at
 ***************************************************************/

namespace hare {
	namespace wrap {
		/******************************************************************
		 * hare::wrap::FD encapsulates a file descriptor to ensure
		 * close() is called also in case of an exception.
		 ******************************************************************/
		class FD {
			int m_fd;	// the encapsulated file descriptor
		public:
			FD() : m_fd(-1) {}
			FD(int fd) : m_fd(fd) {}

			~FD() { if (m_fd != -1) ::close(m_fd); }

			FD& operator=(int fd) {
				if (m_fd)
					::close(m_fd);
				m_fd = fd;
				return *this;
			}

			// use std::shared_ptr instead
			FD(const FD&) = delete;
			FD& operator=(const FD&) = delete;

			// returns zero on success.
			// On error, -1 is returned, and errno is set appropriately.
			int close() {
				if (m_fd != -1) {
					const int result = ::close(m_fd);
					m_fd = -1;
					return result;
				}
				else
					return 0;
			}

			// to use it like a file descriptor
			operator int() const { return m_fd; }
		};
	}	// namespace wrap
}	// namespace hare

#endif	// HARE_UNISTD_H
