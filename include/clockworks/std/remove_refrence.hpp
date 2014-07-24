#if !defined(CW_INCLUDE_REMOVE_REFRENCE)
#define CW_INCLUDE_REMOVE_REFRENCE

namespace ClockWorks {
	namespace std {
		template<class T> struct remove_reference         { typedef T type; };
		template<class T> struct remove_reference < T & > { typedef T type; };
		template<class T> struct remove_reference < T&& > { typedef T type; };
	}
}

#endif