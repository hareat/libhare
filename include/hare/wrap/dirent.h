#ifndef HARE_WRAP_DIRENT_H
#define HARE_WRAP_DIRENT_H

#include <dirent.h>

/***************************************************************************
 * Encapsulates a std C DIR pointer to ensure closing of system ressources.
 *
 * @usage
 * 	const char *path = <your path>;
 *	const hare::wrap::DIR dirp(opendir(path));
 *	if (!dirp)
 *		perror(path);
 *	else {
 *		struct dirent *entry = nullptr;
 *		while ((entry = readdir(dirp))) {
 *			... entry->d_name ...
 *	<automatically closes an open DIR pointer also in case of an exception>
 * or simpler
 *	const hare::wrap::DIR dirp(hare::throws::opendir(<your path>));
 *	struct dirent *entry = nullptr;
 *	while ((entry = hare::throws::readdir(dirp))) {
 *			... entry->d_name ...
 *	...
 *	<automatically closes an open FILE pointer also in case of an exception>
 *
 * @author Hannes Reisinger github@HaRe.at
 **************************************************************************/

#include <hare/system_error>

namespace hare {
	namespace wrap {
		struct DIR {
			DIR() : m_dirp(0) {}
			DIR(::DIR *dirp) : m_dirp(dirp) {}

			~DIR() { if (m_dirp) ::closedir(m_dirp); }

			DIR& operator=(::DIR *dirp) {
				if (m_dirp)
					::closedir(m_dirp);
				m_dirp = dirp;
				return *this;
			}

			// use std::shared_ptr instead
			DIR(const DIR&) = delete;
			DIR& operator=(const DIR&) = delete;

			/// @see man 3 closedir
			/// @return The closedir() function returns 0 on success.
			///         On error, -1 is returned, and errno is set appropriately.
			int closedir()
			{
				if (m_dirp)
				{
					const int result = ::closedir(m_dirp);
					m_dirp = 0;
					return result;
				}
				else
					return 0;
			}

			// to use it like a std C DIR pointer
			operator ::DIR*() const { return m_dirp; }

		private:
			::DIR *m_dirp;
		};

		struct ScandirNamelist {
			ScandirNamelist() : m_namelist(0), m_n(0) {}
			ScandirNamelist(struct dirent **namelist, int n) : m_namelist(namelist), m_n(n) {}
			ScandirNamelist(const char *dir,
				int (*filter)(const struct dirent *),
				int (*compar)(const struct dirent **, const struct dirent **))
				: m_namelist(0), m_n(::scandir(dir, &m_namelist, filter, compar)) {}

			~ScandirNamelist() { free(); }

			// use std::shared_ptr instead
			ScandirNamelist(const ScandirNamelist&) = delete;
			ScandirNamelist& operator=(const ScandirNamelist&) = delete;

			void free() {
				if (m_namelist) {
					for (int i = 0; i < m_n; ++i)
						::free(m_namelist[i]);
					::free(m_namelist);
					m_namelist = 0;
				}
				m_n = 0;
			}

			void reset(struct dirent **namelist, int n) {
				free();
				m_namelist = namelist;
				m_n = n;
			}

			int scandir(const char *dir,
				int (*filter)(const struct dirent *),
				int (*compar)(const struct dirent **, const struct dirent **)) {
				free();
				return (m_n = ::scandir(dir, &m_namelist, filter, compar));
			}

			// usage: for (struct dirent *entry : namelist) ...
			// hare::for_each(namelist, [](struct dirent *entry) { ... });
			// std::for_each(namelist.begin(), namelist.end(), [](struct dirent *entry) { ... });
			struct dirent** begin() const { return m_namelist; }
			struct dirent** end()   const { return m_namelist + m_n; }

		private:
			struct dirent **m_namelist;
			int m_n;
		};
	}	// namespace wrap

	namespace throws {
		inline void closedir(hare::wrap::DIR &dir) {
			if (dir.closedir() == -1)	// see (1) in hare/throws/dirent.h
				throw hare::system_error("%s() failed", __func__);
		}
	}	// namespace throws
}	// namespace hare


// to avoid accidentally calls
inline int closedir(hare::wrap::DIR &dir) { return dir.closedir(); }

#endif	// HARE_WRAP_DIRENT_H
