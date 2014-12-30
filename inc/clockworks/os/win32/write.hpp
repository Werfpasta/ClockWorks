#if !defined(CW_INCL_OS_WIN32_WRITE)
#define CW_INCL_OS_WIN32_WRITE

#include "clockworks\os\win32\call_conventions.hpp"
#include "clockworks\os\win32\types.hpp"

namespace ClockWorks {
	namespace OS {
		namespace Win32 {
			extern "C" {
				const static DWORD STD_OUTPUT_HANDLE = 0xfffffff5;
				const static DWORD STD_INPUT_HANDLE  = 0xfffffff6;
				const static DWORD STD_ERROR_HANDLE  = 0xfffffff4;
				HANDLE CW_WIN32_WINAPI GetStdHandle(DWORD);
				BOOL CW_WIN32_WINAPI WriteFile(HANDLE,PCVOID,DWORD,PDWORD,LPOVERLAPPED);
			}
		}
	}
}
#endif