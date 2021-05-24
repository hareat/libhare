#ifndef TEST_H
#define TEST_H

#include <hare/strprintf>

#include <stdexcept>
#include <string>

#define ASSERT(x) if (!(x)) \
	throw std::runtime_error(hare::strprintf("<%s> failed in %s at line %d", #x, __FILE__, __LINE__));
#define EQUAL_S(l, r) if (std::string(l) != std::string(r)) \
	throw std::runtime_error(hare::strprintf("<\"%s\" != \"%s\"> in %s at line %d", std::string(l).c_str(), std::string(r).c_str(), __FILE__, __LINE__));
#define EQUAL_D(l, r) if (l != r) \
	throw std::runtime_error(hare::strprintf("<%s <%d> != <%d> %s> in %s at line %d", #l, l, r, #r, __FILE__, __LINE__));
#define EQUAL_F(l, r) if (l != r) \
	throw std::runtime_error(hare::strprintf("<%s <%f> != <%f> %s> in %s at line %d", #l, l, r, #r, __FILE__, __LINE__));
#define FAIL(msg) throw std::runtime_error(hare::strprintf("<%s> in %s at line %d", msg, __FILE__, __LINE__));

#endif	// TEST_H
