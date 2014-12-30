#if !defined(CW_INCL_OS_WIN32_TYPES)
#define CW_INCL_OS_WIN32_TYPES
namespace ClockWorks {
	namespace OS {
		namespace Win32 {
			extern "C" {
#				ifndef CW_WIN32_CONST
#					define CW_WIN32_CONST const
#				endif
#				ifndef CW_WIN32_VOID
#					define CW_WIN32_VOID void
#				endif
				typedef char CHAR;
				typedef short SHORT;
				typedef long LONG;
				typedef CHAR CCHAR;
				typedef unsigned char UCHAR,*PUCHAR;
				typedef unsigned short USHORT,*PUSHORT;
				typedef unsigned long ULONG,*PULONG;
				typedef char *PSZ;
				typedef wchar_t WCHAR;
				typedef WCHAR *PWCHAR,*LPWCH,*PWCH,*NWPSTR,*LPWSTR,*PWSTR;
				typedef CW_WIN32_CONST WCHAR *LPCWCH,*PCWCH,*LPCWSTR,*PCWSTR;
				typedef CHAR *PCHAR,*LPCH,*PCH,*NPSTR,*LPSTR,*PSTR;
				typedef CW_WIN32_CONST CHAR *LPCCH,*PCSTR,*LPCSTR;
				typedef unsigned char BYTE;
				typedef unsigned long DWORD;
				typedef int WINBOOL,*PWINBOOL,*LPWINBOOL;
				typedef WINBOOL BOOL;
				typedef char CHAR;
				typedef short SHORT;
				typedef long LONG;
				typedef CHAR CCHAR;
				typedef unsigned char UCHAR,*PUCHAR;
				typedef unsigned short USHORT,*PUSHORT;
				typedef unsigned long ULONG,*PULONG;
				typedef char *PSZ;
				typedef SHORT *PSHORT;
				typedef LONG *PLONG;
				typedef void *HANDLE;
				typedef HANDLE *PHANDLE,*LPHANDLE;
				typedef BOOL *PBOOL,*LPBOOL;
				typedef unsigned short WORD;
				typedef float FLOAT;
				typedef FLOAT *PFLOAT;
				typedef BYTE *PBYTE,*LPBYTE;
				typedef int *PINT,*LPINT;
				typedef WORD *PWORD,*LPWORD;
				typedef long *LPLONG;
				typedef DWORD *PDWORD,*LPDWORD;
				typedef void *PVOID,*LPVOID;
				typedef CW_WIN32_CONST void *PCVOID,*LPCVOID;
				typedef int INT;
				typedef unsigned int UINT,*PUINT,*LPUINT;
				
				typedef struct _OVERLAPPED {
					DWORD Internal;
					DWORD InternalHigh;
					DWORD Offset;
					DWORD OffsetHigh;
					HANDLE hEvent;
				} OVERLAPPED,*POVERLAPPED,*LPOVERLAPPED;
				
				const static HANDLE INVALID_HANDLE_VALUE = reinterpret_cast<HANDLE>(-1);
			}
		}
	}
}
#endif