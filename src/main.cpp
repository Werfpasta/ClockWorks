#define CW_CPP_STRING_(x) #x
#define CW_CPP_STRING(x) CW_CPP_STRING_(x)
#define CW_CPP_JOIN_(x,y) x##y
#define CW_CPP_JOIN(x,y) CW_CPP_JOIN_(x,y)
#define CW_DEBUG_LINE_INFO(x) ClockWorks::IO::Print(CW_CPP_STRING(__FILE__) ":" CW_CPP_STRING(__LINE__) ": ");\
								ClockWorks::IO::Print(x);\
								ClockWorks::IO::Print("\n")
#define CW_DEBUG_LINE ClockWorks::IO::Print(CW_CPP_STRING(__FILE__) ":" CW_CPP_STRING(__LINE__) ": Reached.\n");
#define CW_DEBUG_CALL(x) CW_DEBUG_LINE; void* ret = x; CW_DEBUG_LINE_INFO("Sucess"); return ret;
#define CW_DEBUG_CALL_VOID(x) CW_DEBUG_LINE; x; CW_DEBUG_LINE_INFO("Success");
#define CW_DEBUG

namespace ClockWorks {
	namespace IO {
		unsigned long Print(const char*);
	}
}

#include "clockworks/tinycpp.hpp"

#include "clockworks/io/console.hpp"
#include "clockworks/c_string/itoa.hpp"

int main(int argc, char** argv){
	char str[34] = {0};
	for(int i = 0; i <= 0xFFFFFF; i++){
		ClockWorks::CString::itoa(i,str, 0x10);
		ClockWorks::IO::Print(str);
		ClockWorks::IO::Print(" ");
	}
	return 1;
}