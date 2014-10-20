#if !defined(CW_INCLUDE_ABS)
#define CW_INCLUDE_ABS

#include "clockworks/std/enable_if.hpp"
#include "clockworks/std/is_integral.hpp"
#include "clockworks/std/is_signed.hpp"
#include "clockworks/std/is_floating_point.hpp"

namespace ClockWorks {
	namespace std {
		template < typename T,
				   typename std::enable_if <
					   std::is_integral<T>::value  &&std::is_signed<T>::value
					   >::type * = nullptr >
		int abs(T val) {
			int const mask = val >> (sizeof(T) * 8 /*CHAR_BIT*/ - 1);
			return (val + mask) ^ mask;
		}
		template < typename T,
				   typename std::enable_if <
					   std::is_floating_point<T>::value  &&std::is_signed<T>::value
					   >::type * = nullptr >
		int abs(T val) {
			return (val < 0) ? -val : val;
		}
	}
}

#endif
