#define CW_INCLUDE_IS_NULLPTR_T

#include "clockworks\std\true_false_type.hpp"

namespace ClockWorks {
	namespace std {
		template< class T >
		struct remove_cv {
			typedef typename std::remove_volatile <typename std::remove_const<T>::type >::type type;
		};
		template< class T > struct remove_const { typedef T type; };
		template< class T > struct remove_const<const T> { typedef T type; };
		template< class T > struct remove_volatile { typedef T type; };
		template< class T > struct remove_volatile<volatile T> { typedef T type; };
	}
}