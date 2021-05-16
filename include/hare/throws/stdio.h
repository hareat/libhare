#ifndef HARE_THROWS_STDIO_H
#define HARE_THROWS_STDIO_H

#include <stdio.h>

/***************************************************************************
 * Throws an exception (derived of std::system_error) in case of any error.
 *
 * (1) Many functions return EOF in case of an error and set errno
 *     to indicate the error.
 *
 * (2) Other functions return NULL in case of an error and set errno
 *     to indicate the error.
 *
 * (3) fread and fwrite need an additional call to ferror().
 *
 * No file content is used in error messages. Because this can lead to
 * security troubles. * for char and *** for string is used instead.
 *
 * Many of these functions crash if used with a nullptr.
 * Therefore an argument check for null is also added.
 *
 * @author Hannes Reisinger github@HaRe.at
 ***************************************************************************/

#include <hare/stdexcept>	// CHECK_NOT_NULL_ARG
#include <hare/system_error>

namespace hare {
	namespace throws {
		inline void fclose(FILE *stream) {
			CHECK_NOT_NULL_ARG1(stream);
			if (::fclose(stream) == EOF)	// see (1)
				throw hare::system_error("%s() failed", __func__);
		}

		inline FILE* fdopen(int fd, const char *mode) {
			CHECK_NOT_NULL_ARG1(mode);
			FILE *result = ::fdopen(fd, mode);
			if (result == NULL)		// see (2)
				throw hare::system_error("%s(%d, \"%s\") failed", __func__, fd, mode);
			return result;
		}

		inline void fflush(FILE *stream) {
			CHECK_NOT_NULL_ARG1(stream);
			if (::fflush(stream) == EOF)	// see (1)
				throw hare::system_error("%s() failed", __func__);
		}

		inline int fgetc(FILE *stream) {
			CHECK_NOT_NULL_ARG1(stream);
			int result = ::fgetc(stream);
			if (result == EOF)		// see (1)
				throw hare::system_error("%s() failed", __func__);
			return result;
		}

		inline void fgetpos(FILE *stream, fpos_t *pos) {
			CHECK_NOT_NULL_ARG2(stream, pos);
			if (::fgetpos(stream, pos) == EOF)	// see (1)
				throw hare::system_error("%s() failed", __func__);
		}
		
		inline char* fgets(char *buffer, int size, FILE *stream) {
			CHECK_NOT_NULL_ARG2(buffer, stream);
			char *result = ::fgets(buffer, size, stream);
			if (result == NULL)		// see (2)
				throw hare::system_error("%s(%d) failed", __func__, size);
			return result;
		}

		inline int fileno(FILE *stream) {
			CHECK_NOT_NULL_ARG1(stream);
			int result = ::fileno(stream);
			if (result == EOF)		// see (1)
				throw hare::system_error("%s() failed", __func__);
			return result;
		}

		inline FILE* fmemopen(void *buffer, size_t size, const char *mode) {
			CHECK_NOT_NULL_ARG2(buffer, mode);
			FILE *result = ::fmemopen(buffer, size, mode);
			if (result == NULL)		// see (2)
				throw hare::system_error("%s(%zu, \"%s\") failed", __func__, size, mode);
			return result;
		}

		inline FILE* fopen(const char *path, const char *mode) {
			CHECK_NOT_NULL_ARG2(path, mode);
			FILE *result = ::fopen(path, mode);
			if (result == NULL)		// see (2)
				throw hare::system_error("%s(\"%s\", \"%s\") failed", __func__, path, mode);
			return result;
		}
		inline FILE* fopen(const std::string& path, const char *mode) {
			return hare::throws::fopen(path.c_str(), mode);
		}

		inline int fputc(int ch, FILE *stream) {
			CHECK_NOT_NULL_ARG1(stream);
			int result = ::fputc(ch, stream);
			if (result == EOF)		// see (1)
				throw hare::system_error("%s(*) failed", __func__);
			return result;
		}

		inline void fputs(const char *data, FILE *stream) {
			CHECK_NOT_NULL_ARG2(data, stream);
			if (::fputs(data, stream) == EOF)	// see (1)
				throw hare::system_error("%s(***) failed", __func__);
		}

		inline size_t fread(void *buffer, size_t size, size_t n, FILE *stream) {
			CHECK_NOT_NULL_ARG2(buffer, stream);
			size_t result = ::fread(buffer, size, n, stream);
			if (result != (size * n) && ferror(stream))	// see (3)
				throw hare::system_error("%s(%zu, %zu) failed", __func__, size, n);
			return result;
		}

		inline FILE* freopen(const char *path, const char *mode, FILE *stream) {
			CHECK_NOT_NULL_ARG3(path, mode, stream);
			FILE *result = ::freopen(path, mode, stream);
			if (result == NULL)		// see (2)
				throw hare::system_error("%s(\"%s\", \"%s\") failed", __func__, path, mode);
			return result;
		}
		inline FILE* freopen(const std::string& path, const char *mode, FILE *stream) {
			return hare::throws::freopen(path.c_str(), mode, stream);
		}

		inline size_t fwrite(void *data, size_t size, size_t n, FILE *stream) {
			CHECK_NOT_NULL_ARG2(data, stream);
			size_t result = ::fwrite(data, size, n, stream);
			if (result != (size * n) && ferror(stream))	// see (3)
				throw hare::system_error("%s(%zu, %zu) failed", __func__, size, n);
			return result;
		}

		inline int getc(FILE *stream) {
			CHECK_NOT_NULL_ARG1(stream);
			int result = ::getc(stream);
			if (result == EOF)		// see (1)
				throw hare::system_error("%s() failed", __func__);
			return result;
		}

		inline int getchar() {
			int result = ::getchar();
			if (result == EOF)		// see (1)
				throw hare::system_error("%s() failed", __func__);
			return result;
		}

		inline ssize_t getdelim(char **lineptr, size_t *n, int delim, FILE *stream) {
			CHECK_NOT_NULL_ARG3(lineptr, n, stream);
			ssize_t result = ::getdelim(lineptr, n, delim, stream);
			if (result == EOF)		// see (1)
				throw hare::system_error("%s(0x%X) failed", __func__, delim);
			return result;
		}

		inline ssize_t getline(char **lineptr, size_t *n, FILE *stream) {
			CHECK_NOT_NULL_ARG3(lineptr, n, stream);
			ssize_t result = ::getline(lineptr, n, stream);
			if (result == EOF)		// see (1)
				throw hare::system_error("%s() failed", __func__);
			return result;
		}

		inline FILE* open_memstream(char **bufp, size_t *sizep) {
			CHECK_NOT_NULL_ARG2(bufp, sizep);
			FILE *result = ::open_memstream(bufp, sizep);
			if (result == NULL)		// see (2)
				throw hare::system_error("%s() failed", __func__);
			return result;
		}

		inline void pclose(FILE *stream) {
			CHECK_NOT_NULL_ARG1(stream);
			if (::pclose(stream) == EOF)	// see (1)
				throw hare::system_error("%s() failed", __func__);
		}

		inline FILE* popen(const char *command, const char *mode) {
			CHECK_NOT_NULL_ARG2(command, mode);
			FILE *result = ::popen(command, mode);
			if (result == NULL)		// see (2)
				throw hare::system_error("%s(\"%s\", \"%s\") failed", __func__, command, mode);
			return result;
		}
		inline FILE* popen(const std::string& command, const char *mode) {
			return hare::throws::popen(command.c_str(), mode);
		}

		inline int putc(int c, FILE *stream) {
			CHECK_NOT_NULL_ARG1(stream);
			int result = ::putc(c, stream);
			if (result == EOF)		// see (1)
				throw hare::system_error("%s(*) failed", __func__);
			return result;
		}

		inline int putchar(int c) {
			int result = ::putchar(c);
			if (result == EOF)		// see (1)
				throw hare::system_error("%s(*) failed", __func__);
			return result;
		}

		inline void puts(const char *data) {
			CHECK_NOT_NULL_ARG1(data);
			if (::puts(data) == EOF)	// see (1)
				throw hare::system_error("%s(***) failed", __func__);
		}

		inline void remove(const char *path) {
			CHECK_NOT_NULL_ARG1(path);
			if (::remove(path) == EOF)	// see (1)
				throw hare::system_error("%s(\"%s\") failed", __func__, path);
		}
		inline void remove(const std::string& path) {
			hare::throws::remove(path.c_str());
		}

		inline void rename(const char *oldpath, const char *newpath) {
			CHECK_NOT_NULL_ARG2(oldpath, newpath);
			if (::rename(oldpath, newpath) == EOF)	// see (1)
				throw hare::system_error("%s(\"%s\", \"%s\") failed", __func__, oldpath, newpath);
		}
		inline void rename(const std::string& oldpath, const std::string& newpath) {
			hare::throws::rename(oldpath.c_str(), newpath.c_str());
		}
		inline void rename(const std::string& oldpath, const char *newpath) {
			hare::throws::rename(oldpath.c_str(), newpath);
		}
		inline void rename(const char *oldpath, const std::string& newpath) {
			hare::throws::rename(oldpath, newpath.c_str());
		}

		inline char* tempnam(const char *dir, const char *prefix) {
			char *result = ::tempnam(dir, prefix);
			if (result == NULL)		// see (2)
				throw hare::system_error("%s(\"%s\", \"%s\") failed", __func__, dir, prefix);
			return result;
		}
		inline char* tempnam(const std::string& dir, const std::string& prefix) {
			return hare::throws::tempnam(dir.c_str(), prefix.c_str());
		}
		inline char* tempnam(const std::string& dir, const char *prefix) {
			return hare::throws::tempnam(dir.c_str(), prefix);
		}
		inline char* tempnam(const char *dir, const std::string& prefix) {
			return hare::throws::tempnam(dir, prefix.c_str());
		}
		
		inline FILE* tmpfile() {
			FILE *result = ::tmpfile();
			if (result == NULL)		// see (2)
				throw hare::system_error("%s() failed", __func__);
			return result;
		}

		inline char* tmpnam(char *buffer) {
			char *result = ::tmpnam(buffer);
			if (result == NULL)		// see (2)
				throw hare::system_error("%s() failed", __func__);
			return result;
		}

		inline int ungetc(int c, FILE *stream) {
			CHECK_NOT_NULL_ARG1(stream);
			int result = ::ungetc(c, stream);
			if (result == EOF)		// see (1)
				throw hare::system_error("%s(*) failed", __func__);
			return result;
		}
	}	// namespace throws
}	// namespace hare

#endif	// HARE_THROWS_STDIO_H
