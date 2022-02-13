#ifndef HARE_THROWS_SHM_H
#define HARE_THROWS_SHM_H

#include <sys/shm.h>

/***************************************************************************
 * Throws an exception (derived of std::system_error) in case of any error.
 *
 * @author Hannes Reisinger github@HaRe.at
 ***************************************************************************/

#include <hare/system_error>

namespace hare {
	namespace throws {
		inline int shmctl(int shmid, int cmd, struct shmid_ds *buf) {
			int const result = ::shmctl(shmid, cmd, buf);
			if (result == -1)
				throw hare::system_error("%s(%d, %d, %p) failed", __func__, shmid, cmd, buf);
			return result;
		}
		inline int shmget(key_t key, size_t size, int shmflg) {
			int const result = ::shmget(key, size, shmflg);
			if (result == -1)
				throw hare::system_error("%s(0x%X, %zu, 0%o) failed", __func__, key, size, shmflg);
			return result;
		}
		inline void* shmat(int shmid, const void *shmaddr, int shmflg) {
			void* const result = ::shmat(shmid, shmaddr, shmflg);
			if (result == ((void*) -1))
				throw hare::system_error("%s(%d, %p, %d) failed", __func__, shmid, shmaddr, shmflg);
			return result;
		}
		inline void shmdt(const void *shmaddr) {
			if (::shmdt(shmaddr) == -1)
				throw hare::system_error("%s(%p) failed", __func__, shmaddr);
		}
	}	// namespace throws
}	// namespace hare

#endif	// HARE_THROWS_SHM_H
