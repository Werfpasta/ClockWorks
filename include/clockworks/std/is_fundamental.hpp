#if !defined(CW_INCLUDE_IS_FUNDAMENTAL)
#define CW_INCLUDE_IS_FUNDAMENTAL

#include "clockworks\std\true_false_type.hpp"
#include "clockworks\std\is_integral.hpp"
#include "clockworks\std\is_floating_point.hpp"
#include "clockworks\std\is_void.hpp"
#include "clockworks\std\is_same.hpp"
#include "clockworks\std\nullptr_t.hpp"
#include "clockworks\std\remove_cv.hpp"

namespace ClockWorks {
	namespace std {
		template<class T>
		struct is_fundamental : std::integral_constant < bool,
				is_integral<T>::value || is_floating_point<T>::value || is_void<T>::value ||
				is_same<nullptr_t, typename remove_cv<T>::type>::value > {};
	}
}

#endif