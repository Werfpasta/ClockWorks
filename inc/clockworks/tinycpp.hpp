#if !defined(CW_INCL_TINYCPP)
#	define CW_INCL_TINYCPP
#	include "clockworks/os/os.hpp"
#	if defined(CW_OS_WIN)
#		include "clockworks/os/win32/tinycpp.hpp"
#	else
#		error "Unsupported platform"
#	endif
#	include "clockworks/std/memory.hpp"
#endif