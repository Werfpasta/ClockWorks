#if !defined(CW_INCLUDE_ENABLE_IF)
#define CW_INCLUDE_ENABLE_IF

namespace ClockWorks {
	namespace std {
		template<bool B, class T = void>
		struct enable_if {};

		template<class T>
		struct enable_if<true, T> { typedef T type; };
	}
}

#endif