#ifndef HARE_WRAP_STDIO_H
#define HARE_WRAP_STDIO_H

#include <stdio.h>

/***************************************************************************
 * hare/stdio.h some convenience helper for esp_bt_main.h
 *
 * Encapsulates std C pointers to ensure close is called also in case
 * of an exception.
 *
 * @usage
 * 	const char *path = <your path>;
 *	const hare::wrap::FILE fp(fopen(path, "w"));
 *	if (!fp)
 *		perror(path);
 *	else {
 *		fputs(<your data>, fp);
 *		...
 *	<automatically closes an open FILE pointer also in case of an exception>
 * or simpler
 *	const hare::wrap::FILE fp(hare::throws::fopen(<your path>, "w"));
 *	hare::throws::fputs(<your data>, fp);
 *	...
 *	<automatically closes an open FILE pointer also in case of an exception>
 *
 * @author Hannes Reisinger github@HaRe.at
 ***************************************************************************/

namespace hare {
	namespace wrap {
		/******************************************************************
		 * hare::wrap::FILE encapsulates a std C FILE pointer to ensure
		 * fclose() is called also in case of an exception.
		 ******************************************************************/
		class FILE {
			::FILE *m_fp;	// the encapsulated std C FILE pointer
		public:
			FILE() : m_fp(0) {}
			FILE(::FILE *fp) : m_fp(fp) {}

			~FILE() { if (m_fp) ::fclose(m_fp); }

			FILE& operator=(::FILE *fp) {
				if (m_fp)
					::fclose(m_fp);
				m_fp = fp;
				return *this;
			}

			// use std::shared_ptr instead
			FILE(const FILE&) = delete;
			FILE& operator=(const FILE&) = delete;

			// @see man 3 fclose
			// Upon successful completion 0 is returned.
			// Otherwise, EOF is returned and errno is set to indicate the error.
			int fclose() {
				if (m_fp) {
					const int result = ::fclose(m_fp);
					m_fp = 0;
					return result;
				}
				else
					return 0;
			}

			// to use it like a std C FILE pointer
			operator ::FILE*() const { return m_fp; }
		};

		/******************************************************************
		 * hare::wrap::PIPE encapsulates a std C FILE pointer to ensure
		 * pclose() is called also in case of an exception.
		 ******************************************************************/
		class PIPE {
			::FILE *m_fp;	// the encapsulated std C FILE pointer
		public:
			PIPE() : m_fp(0) {}
			PIPE(::FILE *fp) : m_fp(fp) {}

			~PIPE() { if (m_fp) ::pclose(m_fp); }

			PIPE& operator=(::FILE *fp) {
				if (m_fp)
					::pclose(m_fp);
				m_fp = fp;
				return *this;
			}

			// use std::shared_ptr instead
			PIPE(const PIPE&) = delete;
			PIPE& operator=(const PIPE&) = delete;

			// @see man 3 pclose
			// Upon successful completion 0 is returned.
			// Otherwise, EOF is returned and errno is set to indicate the error.
			int pclose() {
				if (m_fp) {
					const int result = ::pclose(m_fp);
					m_fp = 0;
					return result;
				}
				else
					return 0;
			}

			// to use it like a std C FILE pointer
			operator ::FILE*() const { return m_fp; }
		};
	}	// namespace wrap
}	// namespace hare

#endif	// HARE_WRAP_STDIO_H
