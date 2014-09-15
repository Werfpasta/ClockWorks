#if !defined(CW_INCLUDE_PRINTF)
#define CW_INCLUDE_PRINTF

#include "clockworks\os\os.hpp"
#include <stdarg.h>

namespace ClockWorks {
	namespace std {
		int printf(const char *format, ...) {
			char szBuff[1024];
			int retValue;
			DWORD cbWritten;
			va_list argptr;
			va_start(argptr, format);
			retValue = wvsprintf(szBuff, format, argptr);
			va_end(argptr);
			WriteFile(GetStdHandle(STD_OUTPUT_HANDLE), szBuff, retValue,
					  &cbWritten, 0);
			return retValue;
		}

	}
}

#endif
