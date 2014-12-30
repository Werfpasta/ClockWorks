#if !defined(CW_INCL_CASSERT)
#	define CW_INCL_CASSERT

#ifdef NDEBUG
#define assert(condition) ((void)0)
#else
#define assert(condition) {if(!(condition)){DebugBreak();}}
#endif

#endif