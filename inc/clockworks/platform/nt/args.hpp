#if !defined(CW_INCL_PLATFORM_NT_ARGS)
#define CW_INCL_PLATFORM_NT_ARGS

#include "clockworks/platform/nt/call_conventions.hpp"
#include "clockworks/platform/nt/types.hpp"

namespace ClockWorks {
	namespace OS {
		namespace Win32 {
			extern "C" {
				CW_DECLSPEC_IMPORT LPSTR CW_WINAPI GetCommandLineA();
			}
		}
	}
}
#endif