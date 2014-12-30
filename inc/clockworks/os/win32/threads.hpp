#if !defined(CW_INCL_OS_WIN32_THREADS)
#define CW_INCL_OS_WIN32_THREADS

#include "clockworks/os/win32/types.hpp"

namespace ClockWorks {
	namespace OS {
		namespace Win32 {
			extern "C" {
				CW_WIN32_DECLSPEC_NORETURN void CW_WIN32_WINAPI ExitProcess(UINT);
			}
		}
	}
}

#endif