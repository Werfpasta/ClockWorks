#if !defined(CW_INCLUDE_IS_INTEGRAL)
#define CW_INCLUDE_IS_INTEGRAL

#include "clockworks\std\true_false_type.hpp"

namespace ClockWorks {
	namespace std {
		template<typename T> struct is_integral : std::false_type {};
		template<> struct is_integral<bool> : std::true_type {};
		template<> struct is_integral<char> : std::true_type {};
		template<> struct is_integral<wchar_t> : std::true_type {};
		template<> struct is_integral<signed char> : std::true_type {};
		template<> struct is_integral<short int> : std::true_type {};
		template<> struct is_integral<int> : std::true_type {};
		template<> struct is_integral<long int> : std::true_type {};
		template<> struct is_integral<long long int> : std::true_type {};
		template<> struct is_integral<unsigned char> : std::true_type {};
		template<> struct is_integral<unsigned short int> : std::true_type {};
		template<> struct is_integral<unsigned int> : std::true_type {};
		template<> struct is_integral<unsigned long int> : std::true_type {};
		template<> struct is_integral<unsigned long long int> : std::true_type {};
	}
}

#endif