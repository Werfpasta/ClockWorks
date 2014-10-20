#if !defined(CW_INCLUDE_PAIR)
#define CW_INCLUDE_PAIR

#include "clockworks/std/move.hpp"
#include "clockworks/std/forward.hpp"
#include "clockworks/std/swap.hpp"

namespace ClockWorks {
	namespace std {
		template<typename T1, typename T2>
		class pair {
			public:
				typedef T1 first_type;
				typedef T2 second_type;
				first_type first;
				second_type second;

				pair() : first(), second() {}
				pair(const T1 &x, const T2 &y) : first(x), second(y) {}
				template< class U1, class U2 >
				pair(U1 &&x, U2 &&y) : first(std::forward<U1>(x)), second(std::forward<U2>(y)) {}
				template< class U1, class U2 >
				pair(const pair<U1, U2> &p) : first(p.first), second(p.second) {}
				template< class U1, class U2 >
				pair(pair<U1, U2> &&p) : first(std::move(p.first)), second(std::move(p.second)) {}
				//TODO Tupple initializer
				pair(const pair &p) = default;
				pair(pair &&p) = default;

				pair &operator=(const pair &rhs) {
					first = rhs.first;
					second = rhs.second;
					return *this;
				}
				pair &operator=(pair && rhs) {
					first = std::move(rhs.first);
					second = std::move(rhs.second);
					return *this;
				}
				template< class U1, class U2 >
				pair &operator=(const pair<U1, U2> &rhs) {
					first = rhs.first;
					second = rhs.second;
					return *this;
				}
				template< class U1, class U2 >
				pair &operator=(pair<U1, U2> && rhs) {
					first = std::forward<U1>(rhs.first);
					second = std::forward<U2>(rhs.second);
					return *this;
				}

				void swap(pair &other) {
					std::swap(first, other.first);
					std::swap(second, other.second);
				}
		};

		template< class T1, class T2 >
		std::pair<T1, T2> make_pair(T1 &&t, T2 &&u) {
			return pair<T1, T2>(t, u);
		}

		template< class T1, class T2 >
		bool operator==(const pair<T1, T2> &lhs, const pair<T1, T2> &rhs) {
			return (lhs.first == rhs.first) && (lhs.second == rhs.second);
		}
		template< class T1, class T2 >
		bool operator!=(const pair<T1, T2> &lhs, const pair<T1, T2> &rhs) {
			return !(lhs == rhs);
		}
		template< class T1, class T2 >
		bool operator<(const pair<T1, T2> &lhs, const pair<T1, T2> &rhs) {
			if(lhs.first < rhs.first) { return true; }
			if(rhs.first < lhs.first) { return false; }
			if(lhs.second < rhs.second) { return true; }
			return false;
		}
		template< class T1, class T2 >
		bool operator<=(const pair<T1, T2> &lhs, const pair<T1, T2> &rhs) {
			return !(rhs < lhs);
		}
		template< class T1, class T2 >
		bool operator>(const pair<T1, T2> &lhs, const pair<T1, T2> &rhs) {
			return rhs < lhs;
		}
		template< class T1, class T2 >
		bool operator>=(const pair<T1, T2> &lhs, const pair<T1, T2> &rhs) {
			return !(lhs < rhs);
		}

	}
}

#endif
