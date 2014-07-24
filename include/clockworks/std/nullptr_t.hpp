#if !defined(CW_INCLUDE_NULLPTR_T)
#define CW_INCLUDE_IS_NULLPTR_T

namespace ClockWorks {
	namespace std {
		typedef decltype(nullptr) nullptr_t;
	}
}

#endif