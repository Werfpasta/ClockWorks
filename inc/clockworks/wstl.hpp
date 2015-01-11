#if !defined(CW_INCL_WSTL)
#	define CW_INCL_WSTL
#	if defined(CW_PLATFORM_NT)
#		include "clockworks/platform/nt/wstl.hpp"
#	else
#		error "Unsupported platform"
#	endif
#endif