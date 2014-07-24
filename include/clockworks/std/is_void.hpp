#if !defined(CW_INCLUDE_IS_VOID)
#define CW_INCLUDE_IS_VOID

#include "clockworks\std\true_false_type.hpp"

namespace ClockWorks {
	namespace std {
		template<typename T> struct is_void : std::false_type {};
		template<> struct is_void<void> : std::true_type {};
	}
}

#endif