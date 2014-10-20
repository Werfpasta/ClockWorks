#if !defined(CW_INCLUDE_IS_FLOATING_POINT)
#define CW_INCLUDE_IS_FLOATING_POINT

#include "clockworks/std/true_false_type.hpp"

namespace ClockWorks {
	namespace std {
		template<typename T> struct is_floating_point : std::false_type {};
		template<> struct is_floating_point<float> : std::true_type {};
		template<> struct is_floating_point<double> : std::true_type {};
		template<> struct is_floating_point<long double> : std::true_type {};
	}
}

#endif
