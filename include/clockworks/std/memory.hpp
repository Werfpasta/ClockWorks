#if !defined(CW_INCLUDE_MEMORY)
#define CW_INCLUDE_MEMORY

#include "clockworks/os/os.hpp"

#pragma function(memset, memcpy)
void *memset(void *dest, int count, size_t c) {
	unsigned __int32    size32 = count >> 2;
	unsigned __int32    fill = (c << 24 | c << 16 | c << 8 | c);
	unsigned __int32    *dest32 = (unsigned __int32 *)dest;
	switch((count - (size32 << 2))) {
		case 3:
			((unsigned __int8 *)dest)[count - 3] = unsigned char(c);
		case 2:
			((unsigned __int8 *)dest)[count - 2] = unsigned char(c);
		case 1:
			((unsigned __int8 *)dest)[count - 1] = unsigned char(c);
	}
	while(size32-- > 0) { *(dest32++) = fill; }
	return dest;
}
void *memcpy(void *dest, const void *src, unsigned __int32 count) {
	unsigned __int32    size32 = count >> 2;
	unsigned __int32    *dest32 = (unsigned __int32 *)dest;
	unsigned __int32    *src32 = (unsigned __int32 *)src;
	switch((count - (size32 << 2))) {
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
	while(size32-- > 0) {
		*(dest32++) = *(src32++);
	}
	return dest;
}
void *memmove(void *dest, const void *src, unsigned __int32 count) {
	unsigned __int32    size32 = count >> 2, i;
	unsigned __int32    *dest32 = (unsigned __int32 *)dest;
	unsigned __int32    *src32 = (unsigned __int32 *)src;
	if(dest > src) {
		switch((count - (size32 << 2))) {
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
		while(size32-- > 0) {
			dest32[size32] = src32[size32];
		}
	} else {
		for(i = 0; i < size32; i++) {
			*(dest32++) = *(src32++);
		}
		switch((count - (size32 << 2))) {
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
__declspec(restrict) __declspec(noalias) void *malloc(size_t size) { return HeapAlloc(GetProcessHeap(), 0, size); }
__declspec(restrict) __declspec(noalias) void *calloc(size_t num, size_t size) { return HeapAlloc(GetProcessHeap(), 0x8 /*HEAP_ZERO_MEMORY*/, num * size); }
__declspec(restrict) __declspec(noalias) void *realloc(void *ptr, size_t size) { return HeapReAlloc(GetProcessHeap(), 0, ptr, size); }
__declspec(noalias) void free(void *ptr) { HeapFree(GetProcessHeap(), 0, ptr); }
void *operator new(size_t size) { return malloc(size); }
void *operator new(size_t, void *ptr) { return ptr; }
void operator delete(void *, void *) { return; }
void operator delete(void *p) { free(p); }

#endif
