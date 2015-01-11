#if !defined(CW_INCLUDE_STD_IO_PRINTF)
#	define CW_INCLUDE_STD_IO_PRINTF
#	if defined(CW_PLATFORM_NT)
#		include "clockworks/platform/nt/std/io/printf.hpp"
#	else
#		error "Unsupported platform"
#	endif
#endif