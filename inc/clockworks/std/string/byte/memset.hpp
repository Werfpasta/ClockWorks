#if !defined(CW_INCLUDE_STD_STRING_BYTE_MEMSET)
#define CW_INCLUDE_STD_STRING_BYTE_MEMSET

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wlanguage-extension-token"

namespace std {
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
	}
}

#pragma clang diagnostic pop

#endif