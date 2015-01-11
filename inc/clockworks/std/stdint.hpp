#if !defined(CW_INCL_STD_STDINT)
#	define CW_INCL_STD_STDINT

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wlanguage-extension-token"

namespace std {

	typedef  __int8   int8_t ;
	typedef  __int16  int16_t;
	typedef  __int32  int32_t;
	typedef  __int64  int64_t;
	typedef unsigned __int8  uint8_t ;
	typedef unsigned __int16 uint16_t;
	typedef unsigned __int32 uint32_t;
	typedef unsigned __int64 uint64_t;

#	if defined(CW_OS_WIN)
#		if defined(CW_OS_WIN64)
			typedef uint64_t size_t;
			typedef  int64_t ptrdiff_t;
			typedef  int64_t intptr_t;
#		else
			typedef uint32_t size_t;
			typedef  int32_t ptrdiff_t;
			typedef  int32_t intptr_t;
#		endif
#	endif

}

#pragma clang diagnostic pop

#endif