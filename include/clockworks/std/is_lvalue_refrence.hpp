#if !defined(CW_INCLUDE_IS_LVALUE_REFRENCE)
#define CW_INCLUDE_IS_LVALUE_REFRENCE

namespace ClockWorks {
	namespace std {
		template <typename>
		struct is_lvalue_reference : public false_type {};
		template <typename T>
		struct is_lvalue_reference <T &> : public true_type {};

	}
}

#endif