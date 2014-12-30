#if !defined(CW_INCL_C_STRING_STRLEN)
#define CW_INCL_C_STRING_STRLEN

namespace ClockWorks {
	namespace CString {
		unsigned int strlen(const char* str){
			const char* s;
			for (s = str; *s; ++s);
			return s - str;
		}
	}
}
#endif