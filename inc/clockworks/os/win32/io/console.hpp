#if !defined(CW_INCL_OS_WIN32_IO_CONSOLE)
#define CW_INCL_OS_WIN32_IO_CONSOLE

#include "clockworks/os/win32/types.hpp"
#include "clockworks/os/win32/io.hpp"
#include "clockworks/c_string/strlen.hpp"

namespace ClockWorks {
	namespace IO {
		OS::Win32::DWORD Print(const char* str){
#			pragma clang diagnostic push
#			pragma clang diagnostic ignored "-Wunused-variable"
			const static bool haveConsole = !OS::Win32::AllocConsole() ? true : (DebugBreak(), false);
#			pragma clang diagnostic pop
			const static OS::Win32::HANDLE stdOut =	OS::Win32::GetStdHandle(OS::Win32::STD_OUTPUT_HANDLE)
														!= OS::Win32::INVALID_HANDLE_VALUE
													? OS::Win32::GetStdHandle(OS::Win32::STD_OUTPUT_HANDLE)
													: (DebugBreak(), OS::Win32::INVALID_HANDLE_VALUE);
			OS::Win32::DWORD cbWritten;
			if(!OS::Win32::WriteFile(stdOut, str, CString::strlen(str), &cbWritten, 0)){
				// If the function succeeds, the return value is nonzero (TRUE).
				// If the function fails, or is completing asynchronously, the return value is zero (FALSE).
				// To get extended error information, call the GetLastError function.
				// Note  The GetLastError code ERROR_IO_PENDING is not a failure;
			}
			return cbWritten;
		}
	}
}
#endif