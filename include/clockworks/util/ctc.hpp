#if !defined(CW_INCLUDE_CTC)
#define CW_INCLUDE_CTC

namespace ClockWorks {
	namespace Util {
		template<typename T, T val>
		struct CTC {
			constexpr const static std::uint64_t Value = val;
		};
	}
}

#endif