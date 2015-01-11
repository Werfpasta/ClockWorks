#if !defined(CW_INCL_PLATFORM_NT_STD_IO_PRINTF)
#define CW_INCL_PLATFORM_NT_STD_IO_PRINTF
#include "clockworks/platform/nt/va.hpp"
#include "clockworks/platform/nt/types.hpp"
#include "clockworks/platform/nt/call_conventions.hpp"
namespace ClockWorks {
	namespace OS {
		namespace Win32 {
			extern "C" {
				CW_DECLSPEC_IMPORT int CW_WINAPI wvsprintfA(LPTSTR lpOutput, LPCTSTR lpFmt, va_list arglist);
				CW_DECLSPEC_IMPORT HANDLE CW_WINAPI GetStdHandle(DWORD nStdHandle);
				const DWORD STD_INPUT_HANDLE  = -10;
				const DWORD STD_OUTPUT_HANDLE = -11;
				const DWORD STD_ERROR_HANDLE  = -12;
				CW_DECLSPEC_IMPORT BOOL CW_WINAPI WriteFile(
					HANDLE hFile, LPCVOID lpBuffer, DWORD nNumberOfBytesToWrite,
					LPDWORD lpNumberOfBytesWritten, LPOVERLAPPED lpOverlapped);
			}
		}
	}
}
namespace std {
	int printf(const char* format, ...){
		using namespace ClockWorks::OS::Win32;
		char szBuff[1024];
		int retValue;
		DWORD cbWritten;
		va_list argptr;
		va_start( argptr, format );
		retValue = wvsprintfA( szBuff, format, argptr );
		va_end( argptr );
		WriteFile(GetStdHandle(STD_OUTPUT_HANDLE), szBuff, retValue, &cbWritten, 0);
		return retValue;
	}
}
#endif