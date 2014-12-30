#if !defined(CW_INCLUDE_MEMORY)
#define CW_INCLUDE_MEMORY

#include    "clockworks/os/os.hpp"
#if defined(CW_OS_WIN)
#	include "clockworks/os/win32/memory.hpp"
#else
#	error "Unsupported platform"
#endif

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wlanguage-extension-token"

extern "C" {

	void* memset(void *dest, int count, size_t c) {
		unsigned __int32    size32 = count >> 2;
		unsigned __int32    fill = (c << 24 | c << 16 | c << 8 | c);
		unsigned __int32    *dest32 = (unsigned __int32 *)dest;
		switch ((count - (size32 << 2))) {
		case 3:
			((unsigned __int8 *)dest)[count - 3] = (unsigned char)(c);
		case 2:
			((unsigned __int8 *)dest)[count - 2] = (unsigned char)(c);
		case 1:
			((unsigned __int8 *)dest)[count - 1] = (unsigned char)(c);
		}
		while (size32-- > 0) { *(dest32++) = fill; }
		return dest;
	}
	void* memcpy(void *dest, const void *src, unsigned __int32 count) {
		unsigned __int32    size32 = count >> 2;
		unsigned __int32    *dest32 = (unsigned __int32 *)dest;
		unsigned __int32    *src32 = (unsigned __int32 *)src;
		switch ((count - (size32 << 2))) {
		case 3:
			((unsigned __int8 *)dest)[count - 3] =
				((unsigned __int8 *)src)[count - 3];
		case 2:
			((unsigned __int8 *)dest)[count - 2] =
				((unsigned __int8 *)src)[count - 2];
		case 1:
			((unsigned __int8 *)dest)[count - 1] =
				((unsigned __int8 *)src)[count - 1];
		}
		while (size32-- > 0) {
			*(dest32++) = *(src32++);
		}
		return dest;
	}
	void* memmove(void *dest, const void *src, unsigned __int32 count) {
		unsigned __int32    size32 = count >> 2, i;
		unsigned __int32    *dest32 = (unsigned __int32 *)dest;
		unsigned __int32    *src32 = (unsigned __int32 *)src;
		if (dest > src) {
			switch ((count - (size32 << 2))) {
			case 3:
				((unsigned __int8 *)dest)[count - 1] =
					((unsigned __int8 *)src)[count - 1];
				((unsigned __int8 *)dest)[count - 2] =
					((unsigned __int8 *)src)[count - 2];
				((unsigned __int8 *)dest)[count - 3] =
					((unsigned __int8 *)src)[count - 3];
				break;
			case 2:
				((unsigned __int8 *)dest)[count - 1] =
					((unsigned __int8 *)src)[count - 1];
				((unsigned __int8 *)dest)[count - 2] =
					((unsigned __int8 *)src)[count - 2];
				break;
			case 1:
				((unsigned __int8 *)dest)[count - 1] =
					((unsigned __int8 *)src)[count - 1];
				break;
			}
			while (size32-- > 0) {
				dest32[size32] = src32[size32];
			}
		}
		else {
			for (i = 0; i < size32; i++) {
				*(dest32++) = *(src32++);
			}
			switch ((count - (size32 << 2))) {
			case 3:
				*(dest32++) = *(src32++);
			case 2:
				*(dest32++) = *(src32++);
			case 1:
				*(dest32++) = *(src32++);
			}
		}
		return dest;
	}
}

#if defined(CW_DEBUG)
void* operator new(size_t size){CW_DEBUG_CALL(malloc(size));}
void* operator new(size_t, void* ptr){CW_DEBUG_LINE; void* ret = ptr; CW_DEBUG_LINE_INFO("2"); return ret;}
void  operator delete(void*, void*) {CW_DEBUG_CALL_VOID()}
void  operator delete(void* p) noexcept {CW_DEBUG_CALL_VOID(free(p));}
#else
void* operator new(size_t size){return malloc(size);}
void* operator new(size_t, void* ptr){return ptr;}
void  operator delete(void*, void*) {}
void  operator delete(void* p) noexcept {free(p);}
#endif

#pragma clang diagnostic pop

#endif
