#if !defined(CW_INCLUDE_IS_INTEGRAL)
#define CW_INCLUDE_IS_INTEGRAL

#include "clockworks\std\true_false_type.hpp"

namespace ClockWorks {
	namespace std {
		template<typename T> struct is_arithmetic : std::false_type {};
		template<> struct is_arithmetic<bool> : std::true_type {};
		template<> struct is_arithmetic<char> : std::true_type {};
		template<> struct is_arithmetic<wchar_t> : std::true_type {};
		template<> struct is_arithmetic<signed char> : std::true_type {};
		template<> struct is_arithmetic<short int> : std::true_type {};
		template<> struct is_arithmetic<int> : std::true_type {};
		template<> struct is_arithmetic<long int> : std::true_type {};
		template<> struct is_arithmetic<long long int> : std::true_type {};
		template<> struct is_arithmetic<unsigned char> : std::true_type {};
		template<> struct is_arithmetic<unsigned short int> : std::true_type {};
		template<> struct is_arithmetic<unsigned int> : std::true_type {};
		template<> struct is_arithmetic<unsigned int> : std::true_type {};
		template<> struct is_arithmetic<unsigned long long int> : std::true_type {};
		template<> struct is_arithmetic<float> : std::true_type {};
		template<> struct is_arithmetic<double> : std::true_type {};
		template<> struct is_arithmetic<long double> : std::true_type {};
	}
}

#endif