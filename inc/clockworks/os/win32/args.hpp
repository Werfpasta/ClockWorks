#if !defined(CW_INCL_OS_WIN32_ARGS)
#define CW_INCL_OS_WIN32_ARGS

#include "clockworks/os/win32/call_conventions.hpp"
#include "clockworks/os/win32/types.hpp"

namespace ClockWorks {
	namespace OS {
		namespace Win32 {
			extern "C" {
				CW_WIN32_DECLSPEC_IMPORT LPSTR CW_WIN32_WINAPI GetCommandLineA();
			}
		}
	}
}
#endif