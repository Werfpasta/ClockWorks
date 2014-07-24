#if !defined(CW_INCLUDE_INTEGRAL_CONSTANT)
#define CW_INCLUDE_TRUE_INTEGRAL_CONSTANT

namespace ClockWorks {
	namespace std {
		template<typename T, T value>
		struct integral_constant {
			static constexpr T value = value;
			typedef T value_type;
			typedef integral_constant<T, value> type;
			constexpr operator value_type() { return value; }
		};
	}
}

#endif