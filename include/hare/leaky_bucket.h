#ifndef HARE_LEAKY_BUCKET_H
#define HARE_LEAKY_BUCKET_H

/***************************************************************
 * hare/leaky_bucket.h a simple class for a leaky bucket.
 * see https://en.wikipedia.org/wiki/Leaky_bucket
 *
 * These implementations do not take care about units,
 * the caller has to do this.
 * Also take care about calculating the current level (by calling
 * elapsed) *before* you pour new stuff into the bucket.
 *
 * @author Hannes Reisinger github@HaRe.at
 ***************************************************************/

namespace hare {
	/*****************************************************************
	 * This most general class can also be called on a fixed amount
	 * of time base instead of the following classes.
	 *****************************************************************/
	template <class size_type = size_t>
	struct leaky_bucket {
		leaky_bucket(size_t capacity, size_t leak_rate)
			: m_capacity(capacity), m_leak_rate(leak_rate), m_level(0) {}

		size_type capacity()  const { return m_capacity; }
		size_type leak_rate() const { return m_leak_rate; }
		size_type level()     const { return m_level; }

		// @return overflow. 0 means no overflow
		size_type pour(size_type amount) {
			m_level += amount;
			if (m_level > m_capacity) {
				size_type overflow = m_level - m_capacity;
				m_level = m_capacity;
				return overflow;
			}
			return 0;
		}

		// @return the leaky bucket itself. so you can make meaningful calls like
		//         size_t overflow = my_leaky_bucket.elapsed(time_diff).pour(mbit);
		leaky_bucket& elapsed(size_type time_diff) {
			size_type leaked = time_diff * m_leak_rate;
			if (m_level > leaked)
				m_level -= leaked;
			else
				m_level = 0;	// the level in the bucket can never be less than 0
			return *this;
		}

	private:
		size_type m_capacity;
		size_type m_leak_rate;
		size_type m_level;
	};


	/*****************************************************************
	 * This class additionally records the last time when the leak
	 * was calculated.
	 * So all you have to do is pour something inside your bucket.
	 * See TestHareLeakyBucket for an example.
	 *****************************************************************/
	template <class time_functor, class size_type = size_t>
	struct leaky_bucket_t : public leaky_bucket<size_type> {
		leaky_bucket_t(size_type capacity, size_type leak_rate)
			: leaky_bucket<size_type>(capacity, leak_rate)
			, m_time_functor(time_functor()), m_last_call(m_time_functor()) {}

		// @return overflow. 0 means no overflow
		size_type pour(size_type amount) {
			typename time_functor::result_type t = m_time_functor();
			leaky_bucket<size_type>::elapsed(t - m_last_call);
			m_last_call = t;
			return leaky_bucket<size_type>::pour(amount);
		}

	private:
		time_functor m_time_functor;
		typename time_functor::result_type m_last_call;

		using leaky_bucket<size_type>::elapsed;	// hide it to avoid misuse
	};
}	// namespace hare

#endif	// HARE_LEAKY_BUCKET_H
