#if !defined(CW_INCL_OS_WIN32_CALL_CONVENTIONS)
#define CW_INCL_OS_WIN32_CALL_CONVENTIONS
namespace ClockWorks {
	namespace OS {
		namespace Win32 {
			extern "C" {
#				if defined(CW_OS_WIN32)
#					define CW_WIN32_WINAPI __stdcall /* TODO: Huh attibute apparently does not go here? [[gnu::stdcall]] */
#				else
#					define CW_WIN32_WINAPI
#				endif
#				define CW_WIN32_DECLSPEC_IMPORT __declspec(dllimport) /* [[gnu::dllimport]] */
#				define CW_WIN32_DECLSPEC_NORETURN __declspec(noreturn)
			}
		}
	}
}
#endif