#if !defined(CW_INCLUDE_SWAP)
#define CW_INCLUDE_SWAP

namespace ClockWorks {
	namespace std {
		template<typename T>
		void swap(T &lhs, T &rhs) {
			T   tmp = lhs;
			lhs = rhs;
			rhs = tmp;
		}
	}
}

#endif