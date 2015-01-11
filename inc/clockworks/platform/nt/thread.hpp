#if !defined(CW_INCL_PLATFORM_NT_THREAD)
#define CW_INCL_PLATFORM_NT_THREAD

#include "clockworks/platform/nt/types.hpp"

namespace ClockWorks {
	namespace OS {
		namespace Win32 {
			extern "C" {
				CW_DECLSPEC_NORETURN void CW_WINAPI ExitProcess(UINT);
			}
		}
	}
}

#endif