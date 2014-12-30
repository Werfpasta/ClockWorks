#if !defined(CW_INCL_OS_WIN32_TINYCPP)
#define CW_INCL_OS_WIN32_TINYCPP

#include "clockworks/os/win32/args.hpp"
#include "clockworks/os/win32/threads.hpp"

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wlanguage-extension-token"

__inline__ __attribute__((always_inline)) void DebugBreak() {_asm {int 3}} 

extern "C" {
	#if defined(CW_GUI)
	int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
					   LPSTR szCmdLine, int iCmdShow);
	#else
	int main(int argc, char **argv);
	#endif
	int /*WINAPI*/ CWMain() {
		char *lpszCommandLine = ClockWorks::OS::Win32::GetCommandLineA();
		if(*lpszCommandLine == '"') {
			while(*lpszCommandLine && (*lpszCommandLine != '"')) { lpszCommandLine++; }
			if(*lpszCommandLine == '"') { lpszCommandLine++; }
		} else {
			while(*lpszCommandLine > ' ') { lpszCommandLine++; }
		}
		while(*lpszCommandLine && (*lpszCommandLine <= ' ')) { lpszCommandLine++; }
		int mainret;
		#if defined(CW_GUI)
		STARTUPINFO StartupInfo = { sizeof(STARTUPINFO), 0 };
		mainret = WinMain(GetModuleHandle(NULL), NULL, lpszCommandLine,
						  (StartupInfo.dwFlags & STARTF_USESHOWWINDOW) ? StartupInfo.wShowWindow :
						  SW_SHOWDEFAULT);
		#else
		#include "clockworks/os/win32/main.hpp"
		//mainret = main(0, &lpszCommandLine);  //TODO: Proper argc/v parsing.
		#endif
		ClockWorks::OS::Win32::ExitProcess(mainret);
		return mainret;
	}
}

#pragma clang diagnostic pop

#endif
