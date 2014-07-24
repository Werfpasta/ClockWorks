#if !defined(CW_INCLUDE_FORWARD)
#define CW_INCLUDE_FORWARD

#include "clockworks\std\remove_refrence.hpp"
#include "clockworks\std\is_lvalue_refrence.hpp"

namespace ClockWorks {
	namespace std {
		template<typename T>
		inline T &&
		forward(typename std::remove_reference<T>::type &t) {
			return static_cast < T && >(t);
		}

		template<typename T>
		inline T &&
		forward(typename std::remove_reference<T>::type &&t) {
			static_assert(!std::is_lvalue_reference<T>::value, "LValue");
			return static_cast < T && >(t);
		}
	}
}

#endif