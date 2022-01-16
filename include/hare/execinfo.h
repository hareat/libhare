#ifndef HARE_BACKTRACE
#define HARE_BACKTRACE

#include <execinfo.h>

/**************************************************************************
 * <hare/execinfo.h> handy convenience methods for <execinfo.h>.
 *
 * @author Hannes Reisinger github@HaRe.at
 **************************************************************************/

#ifdef BACKTRACE_SIZE
#include <execinfo.h>	// backtrace
#ifdef BACKTRACE_ADDR2LINE
#include <hare/signalsafe/writef>
#include <string.h>		// strchr
#endif	// BACKTRACE_ADDR2LINE
#else	// !BACKTRACE_SIZE
#include <hare/signalsafe/write>
#endif	// BACKTRACE_SIZE

namespace hare {
	/**********************************************************************
	 * A backtrace is often helpful in error analysis.
	 **********************************************************************/
	struct backtrace {
#ifdef BACKTRACE_SIZE
	private:
		void *m_backtrace[BACKTRACE_SIZE];
		int   m_backtrace_size;
	public:
		backtrace() { m_backtrace_size = ::backtrace(m_backtrace, BACKTRACE_SIZE); }

		char** backtrace_symbols() const { return ::backtrace_symbols(m_backtrace, m_backtrace_size); }
		void backtrace_symbols_fd(int fd) const { ::backtrace_symbols_fd(m_backtrace, m_backtrace_size, fd); }
		void backtrace_addr2line_fd(int fd) const {
#ifdef BACKTRACE_ADDR2LINE
			char **symbols = backtrace_symbols();
			if (symbols) {
				for (size_t i = 0; i < m_backtrace_size; ++i) {
					const char *mangled = symbols[i];
					// format: file(function+offset) [address]
					const char *pos1 = strchr(mangled, '(');
					if (pos1) {
						const char *pos2 = strchr(pos1 + 1, ')');
						if (pos2) {
							hare::signalsafe::write(fd, "addr2line -e ");
							hare::signalsafe::write(fd, mangled, pos1 - mangled);
							hare::signalsafe::write(fd, " ");
							hare::signalsafe::write(fd, pos1 + 1, pos2 - pos1 - 1);
							hare::signalsafe::write(fd, "\n");
						} else
							hare::signalsafe::writef(fd, "%s\n", mangled);
					} else
						hare::signalsafe::writef(fd, "%s\n", mangled);
				}
				free(symbols);
			} else {
				backtrace_symbols_fd(fd);
				hare::signalsafe::writef(fd, "in %s also %s failed\n", __func__, "backtrace_symbols");
			}
#else	// !BACKTRACE_ADDR2LINE
			backtrace_symbols_fd(fd);
#endif	// BACKTRACE_ADDR2LINE
		}
#else	// !BACKTRACE_SIZE
		char** backtrace_symbols() const { return NULL; }
		void backtrace_symbols_fd(int fd) const { hare::signalsafe::write(fd,
			"No backtrace available. Please compile with -DBACKTRACE_SIZE=<number>\n"); }
		void backtrace_addr2line_fd(int fd) const { backtrace_symbols_fd(fd); }
#endif	// BACKTRACE_SIZE
	};
}	// namespace hare

#endif	// HARE_BACKTRACE
