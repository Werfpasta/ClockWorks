#if !defined(CW_INCLUDE_TINYCPP)
#define CW_INCLUDE_TINYCPP

#include "clockworks\os\os.hpp"

#include "clockworks\std\memory.hpp"

#pragma comment(linker, "/INCREMENTAL:NO")
#pragma comment(linker, "/NODEFAULTLIB")
#pragma comment(linker, "/MERGE:.rdata=.text")

#define DebugBreak() _asm {int 3}

extern "C" {

	int _fltused = 0; // Useless symbol injected by MSVC for floating point support.

	// Static initializers

	typedef void(*_PVFV)();

	// Behold a un-ignorable linker warning.
//#pragma comment(linker, "/ignore:4210") // .CRT section exists; there may be unhandled static initializers or terminators
#pragma data_seg(".CRT$XCA")
	_PVFV __xc_a[] = { NULL };
#pragma data_seg(".CRT$XCZ")
	_PVFV __xc_z[] = { NULL };
#pragma data_seg()

	void __cdecl _InitializeTerminate(_PVFV *pfbegin, _PVFV *pfend) {
		while(pfbegin < pfend) {
			if(*pfbegin != NULL) { (**pfbegin)(); }
			++pfbegin;
		}
	}

	static _PVFV *_AtExitFuncList = 0;
	static unsigned _AtExitMax = 32;
	static unsigned _AtExitEntries = 0;

	void __cdecl _InitAtExit(void) {
		_AtExitFuncList = (_PVFV *)HeapAlloc(GetProcessHeap(), _AtExitMax, sizeof(_PVFV *));
	}

	int __cdecl atexit(_PVFV func) {
		if(_AtExitEntries < _AtExitMax) {
			_AtExitFuncList[_AtExitEntries++] = func;
			return 0;
		}
		return -1;
	}

	void __cdecl _DoExit(void) {
		if(_AtExitEntries) {
			_InitializeTerminate(_AtExitFuncList, _AtExitFuncList + _AtExitEntries);
		}
	}

	#if defined(CW_GUI)
	int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
					   LPSTR szCmdLine, int iCmdShow);
	#else
	int main(int argc, char **argv);
	#endif

#pragma comment(linker, "/ENTRY:CWMain")
	int WINAPI CWMain() {
		_InitAtExit();
		_InitializeTerminate(__xc_a, __xc_z);
		char *lpszCommandLine = GetCommandLineA();
		if(*lpszCommandLine == '"') {
			while(*lpszCommandLine && (*lpszCommandLine != '"')) { lpszCommandLine++; }
			if(*lpszCommandLine == '"') { lpszCommandLine++; }
		} else {
			while(*lpszCommandLine > ' ') { lpszCommandLine++; }
		}
		while(*lpszCommandLine && (*lpszCommandLine <= ' ')) { lpszCommandLine++; }
		int mainret;
		#if defined(CW_WINMAIN)
		STARTUPINFO StartupInfo = { sizeof(STARTUPINFO), 0 };
		GetStartupInfo(&StartupInfo);
		mainret = WinMain(GetModuleHandle(NULL), NULL, lpszCommandLine,
						  (StartupInfo.dwFlags & STARTF_USESHOWWINDOW) ? StartupInfo.wShowWindow :
						  SW_SHOWDEFAULT);
		#else
		mainret = main(0, &lpszCommandLine);  //TODO: Proper argc/v parsing.
		#endif
		_DoExit();
		ExitProcess(mainret);
		#if 0
		return mainret;
		#endif
	}

	int _cdecl _purecall(void) { DebugBreak(); return 0; } // Hopefully this never happens.

}

#endif
