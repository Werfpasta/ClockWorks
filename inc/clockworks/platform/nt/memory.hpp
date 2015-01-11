#if !defined(CW_INCL_PLATFORM_NT_MEMORY)
#define CW_INCL_PLATFORM_NT_MEMORY

#include "clockworks/platform/nt/types.hpp"
#include "clockworks/platform/nt/call_conventions.hpp"

namespace ClockWorks {
	namespace OS {
		namespace Win32 {
			extern "C" {
				const auto HEAP_NO_SERIALIZE             = 1;
				const auto HEAP_GROWABLE                 = 2;
				const auto HEAP_GENERATE_EXCEPTIONS      = 4;
				const auto HEAP_ZERO_MEMORY              = 8;
				const auto HEAP_REALLOC_IN_PLACE_ONLY    = 16;
				const auto HEAP_TAIL_CHECKING_ENABLED    = 32;
				const auto HEAP_FREE_CHECKING_ENABLED    = 64;
				const auto HEAP_DISABLE_COALESCE_ON_FREE = 128;
				const auto HEAP_CREATE_ALIGN_16          = 0x0000;
				const auto HEAP_CREATE_ENABLE_TRACING    = 0x20000;
				const auto HEAP_MAXIMUM_TAG              = 0xFFF;
				const auto HEAP_PSEUDO_TAG_FLAG          = 0x8000;
				const auto HEAP_TAG_SHIFT                = 16;
#				define CW_WIN32_HEAP_MAKE_TAG_FLAGS(b,o) ((ClockWorks::OS::Win32::DWORD)((b)+(o)<<16)))

				CW_DECLSPEC_IMPORT HANDLE CW_WINAPI GetProcessHeap(CW_WIN32_VOID);
				CW_DECLSPEC_IMPORT PVOID  CW_WINAPI HeapAlloc     (HANDLE,DWORD,DWORD);
				CW_DECLSPEC_IMPORT PVOID  CW_WINAPI HeapReAlloc   (HANDLE,DWORD,PVOID,DWORD);
				CW_DECLSPEC_IMPORT BOOL   CW_WINAPI HeapFree      (HANDLE,DWORD,PVOID);
			}
		}
	}
}

extern "C" {
	void* malloc (size_t size) { return ClockWorks::OS::Win32::HeapAlloc(ClockWorks::OS::Win32::GetProcessHeap(), 0, size); }
	void* calloc (size_t num, size_t size) { return ClockWorks::OS::Win32::HeapAlloc(ClockWorks::OS::Win32::GetProcessHeap(), ClockWorks::OS::Win32::HEAP_ZERO_MEMORY, num * size); }
	void* realloc(void *ptr, size_t size)  { return ClockWorks::OS::Win32::HeapReAlloc(ClockWorks::OS::Win32::GetProcessHeap(), 0, ptr, size); }
	void  free   (void *ptr) { ClockWorks::OS::Win32::HeapFree(ClockWorks::OS::Win32::GetProcessHeap(), 0, ptr); }
}

#endif