#if !defined(CW_INCLUDE_IS_SIGNED)
#define CW_INCLUDE_IS_SIGNED

#include "clockworks\std\true_false_type.hpp"

namespace ClockWorks {
	namespace std {
		template<typename T> struct is_signed : std::false_type {};
		template<> struct is_signed<bool> : std::true_type {};
		template<> struct is_signed<wchar_t> : std::true_type {};
		template<> struct is_signed<signed char> : std::true_type {};
		template<> struct is_signed<short int> : std::true_type {};
		template<> struct is_signed<int> : std::true_type {};
		template<> struct is_signed<long int> : std::true_type {};
		template<> struct is_signed<float> : std::true_type {};
		template<> struct is_signed<double> : std::true_type {};
		template<> struct is_signed<long double> : std::true_type {};
	}
}

#endif