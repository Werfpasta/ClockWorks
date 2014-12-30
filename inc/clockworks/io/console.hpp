#if !defined(CW_INCL_IO_CONSOLE)
#	define CW_INCL_IO_CONSOLE
#	include "clockworks/os/os.hpp"
#	if defined(CW_OS_WIN)
#		include "clockworks/os/win32/io/console.hpp"
#	else
#		error "Unsupported platform"
#	endif
#endif