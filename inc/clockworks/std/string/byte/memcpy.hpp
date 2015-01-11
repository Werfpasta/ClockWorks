#if !defined(CW_INCLUDE_STD_STRING_BYTE_MEMCPY)
#define CW_INCLUDE_STD_STRING_BYTE_MEMCPY
namespace std {
	void* memcpy(void *dest, const void *src, unsigned __int32 count) {
		unsigned __int32	 size32 = count >> 2;
		unsigned __int32	*dest32 = (unsigned __int32 *)dest;
		unsigned __int32	*src32  = (unsigned __int32 *)src;
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
}
#endif