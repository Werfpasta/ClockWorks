#if !defined(CW_INCLUDE_TRUE_FALSE_TYPE)
#define CW_INCLUDE_TRUE_FALSE_TYPE

#include "clockworks\std\integral_constant.hpp"

namespace ClockWorks {
	namespace std {
		typedef integral_constant<bool, true> true_type;
		typedef integral_constant<bool, false> false_type;
	}
}

#endif