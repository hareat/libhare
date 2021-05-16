#ifndef HARE_LITERALS_H
#define HARE_LITERALS_H

/***************************************************************
 * hare/literals.h handy user-defined literals.
 *
 * @author Hannes Reisinger github@HaRe.at
 ***************************************************************/

/***************************************************************
 * Descriptive literals for a notation like sleep(50_s).
 ***************************************************************/

// Seconds
inline unsigned long long operator"" _s(unsigned long long x) {
  return x;
}
// Milliseconds
inline unsigned long long operator"" _ms(unsigned long long x) {
  return x;
}

// Meters
inline unsigned long long operator"" _m(unsigned long long x) {
  return x;
}
// Kilometers
inline unsigned long long operator"" _km(unsigned long long x) {
  return x;
}


/***************************************************************
 * Converting literals for function calls like sleep(1_h2s).
 ***************************************************************/

// Minutes to Seconds
inline unsigned long long operator"" _m2s(unsigned long long x) {
  return x * 60ULL;
}
// Hours to Seconds
inline unsigned long long operator"" _h2s(unsigned long long x) {
  return x * 3600ULL;
}
// Days to Seconds
inline unsigned long long operator"" _d2s(unsigned long long x) {
  return x * 86400ULL;
}
// Weeks to Seconds
inline unsigned long long operator"" _w2s(unsigned long long x) {
  return x * 604800ULL;
}
// Seconds to Milliseconds
inline unsigned long long operator"" _s2ms(unsigned long long x) {
  return x * 1000ULL;
}
// Minutes to Milliseconds
inline unsigned long long operator"" _m2ms(unsigned long long x) {
  return x * 60000ULL;
}
// Hours to Milliseconds
inline unsigned long long operator"" _h2ms(unsigned long long x) {
  return x * 3600000ULL;
}
// Days to Milliseconds
inline unsigned long long operator"" _d2ms(unsigned long long x) {
  return x * 86400000ULL;
}
// Weeks to Milliseconds
inline unsigned long long operator"" _w2ms(unsigned long long x) {
  return x * 604800000ULL;
}
// Seconds to Microseconds
inline unsigned long long operator"" _s2us(unsigned long long x) {
  return x * 1000000ULL;
}
// Minutes to Microseconds
inline unsigned long long operator"" _m2us(unsigned long long x) {
  return x * 60000000ULL;
}
// Hours to Microseconds
inline unsigned long long operator"" _h2us(unsigned long long x) {
  return x * 3600000000ULL;
}
// Days to Microseconds
inline unsigned long long operator"" _d2us(unsigned long long x) {
  return x * 86400000000ULL;
}
// Weeks to Microseconds
inline unsigned long long operator"" _w2us(unsigned long long x) {
  return x * 604800000000ULL;
}

// Kilometers to Meters
inline unsigned long long operator"" _km2m(unsigned long long x) {
  return x * 1000ULL;
}

#endif	// HARE_LITERALS_H
