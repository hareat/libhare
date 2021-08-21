#ifndef HARE_SIGNALSAFE_UNISTD_H
#define HARE_SIGNALSAFE_UNISTD_H

#include <unistd.h>

/***************************************************************
 * hare/signalsafe/unistd.h async-signal-safe functions of unistd.h.
 * Only functions of the list in man signal-safety are allowed.
 *
 * @author Hannes Reisinger github@HaRe.at
 ***************************************************************/

namespace hare {
	namespace signalsafe {
		using ::access;
		using ::alarm;
		using ::chdir;
		using ::chown;
		using ::close;
		using ::dup;
		using ::dup2;
		using ::execl;
		using ::execle;
		using ::execv;
		using ::execve;
		using ::_exit;
		using ::faccessat;
		using ::fchdir;
		using ::fchown;
		using ::fchownat;
		using ::fdatasync;
		using ::fexecve;
		using ::fork;
		using ::fsync;
		using ::ftruncate;
		using ::getegid;
		using ::geteuid;
		using ::getgid;
		using ::getgroups;
		using ::getpgrp;
		using ::getpid;
		using ::getppid;
		using ::getuid;
		using ::link;
		using ::linkat;
		using ::lseek;
		using ::pause;
		using ::pipe;
		using ::read;
		using ::readlink;
		using ::readlinkat;
		using ::rmdir;
		using ::setgid;
		using ::setpgid;
		using ::setsid;
		using ::setuid;
		using ::sleep;
		using ::symlink;
		using ::symlinkat;
		using ::unlink;
		using ::unlinkat;

		inline ssize_t write(int fd, const void *buf, size_t count) {
			if (buf && count)
				return ::write(fd, buf, count);
			else
				return 0;
		}
	}	// namespace signalsafe
}	// namespace hare

#endif	// HARE_SIGNALSAFE_UNISTD_H
