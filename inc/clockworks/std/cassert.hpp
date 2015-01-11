#if !defined(CW_INCL_STD_CASSERT)
#	include "clockworks/debug.hpp"
#	define CW_INCL_STD_CASSERT
#	ifdef NDEBUG
#		define assert(condition) ((void)0)
#	else
#		define assert(condition) {if(!(condition)){DebugBreak();}}
#	endif
#endif