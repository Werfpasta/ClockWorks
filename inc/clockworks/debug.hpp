#if !defined(CW_INCL_DEBUG)
#define CW_INCL_DEBUG
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wlanguage-extension-token"
namespace ClockWorks {
	void DebugBreak(){ __asm{int 3}; }
}
#pragma clang diagnostic pop
#endif