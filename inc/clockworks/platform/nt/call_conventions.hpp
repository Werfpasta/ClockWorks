#if !defined(CW_INCL_PLATFORM_NT_CALL_CONVENTIONS)
#define CW_INCL_PLATFORM_NT_CALL_CONVENTIONS
namespace ClockWorks {
	namespace OS {
		namespace Win32 {
			extern "C" {
#				define CW_WINAPI __stdcall /* TODO: Huh attibute apparently does not go here? [[gnu::stdcall]] */
#				define CW_DECLSPEC_IMPORT __declspec(dllimport) /* [[gnu::dllimport]] */
#				define CW_DECLSPEC_NORETURN __declspec(noreturn)
			}
		}
	}
}
#endif