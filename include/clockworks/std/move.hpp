#if !defined(CW_INCLUDE_MOVE)
#define CW_INCLUDE_MOVE

#include "clockworks/std/remove_refrence.hpp"

namespace ClockWorks {
	namespace std {
		template <typename T>
		typename remove_reference<T>::type &&move(T &&arg) {
			return static_cast < typename remove_reference<T>::type && >(arg);
		}
	}
}

#endif
