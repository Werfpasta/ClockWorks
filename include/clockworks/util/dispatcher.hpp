#if !defined(CW_INCLUDE_DISPATCHER)
#define CW_INCLUDE_DISPATCHER

#include "clockworks/util/delegate.hpp"
#include "clockworks/std/vector.hpp"
#include "clockworks/std/is_void.hpp"
#include "clockworks/std/enable_if.hpp"

namespace ClockWorks {
	namespace Util {
		template <typename TSignature> class Dispatcher;
		template <typename R, typename ... A>
		class Dispatcher < R(A...)> : public ClockWorks::std::vector<Delegate<R(A...)>> {
				typedef R ReturnType;
			public:
				typedef Delegate<R(A...)> DelegateT;
				template<typename RetType = R>
				typename std::enable_if < !std::is_void<RetType>::value, std::vector<RetType >>::type
				operator()(A ... a) const {
					std::vector<RetType> ret;
					for(auto &d : *this) {
						ret.push_back(d(a...));
					}
					return ret;
				}
				template<typename RetType = R>
				typename std::enable_if<std::is_void<RetType>::value, void>::type
				operator()(A ... a) const {
					for(auto &d : *this) {
						d(a...);
					}
				}
		};
	}
}

#endif
