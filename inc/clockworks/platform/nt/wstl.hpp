#if !defined(CW_INCL_PLATFORM_NT_TINYCPP)
#define CW_INCL_PLATFORM_NT_TINYCPP

#include "clockworks/platform/nt/args.hpp"
#include "clockworks/platform/nt/thread.hpp"
#include "clockworks/platform/nt/memory.hpp"

extern "C" {
	#if defined(CW_GUI)
	int CW_WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
					   LPSTR szCmdLine, int iCmdShow);
	#else
	int main(int argc, char** argv);
	#endif
	int CW_WINAPI CWMain() {
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
		#pragma clang diagnostic push
		#pragma clang diagnostic ignored "-Wmain"
		mainret = main(0, 0);  //TODO: Proper argc/v parsing.
		#pragma clang diagnostic pop
		#endif
		ClockWorks::OS::Win32::ExitProcess(mainret);
		return mainret;
	}
}

#endif