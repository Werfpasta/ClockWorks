#if !defined(CW_INCLUDE_IS_SAME)
#define CW_INCLUDE_IS_SAME

#include "clockworks\std\true_false_type.hpp"

namespace ClockWorks {
	namespace std {
		template<typename T, typename U> struct is_same : std::false_type {};
		template<typename T> struct is_same<T, T> : std::true_type {};
	}
}

#endif