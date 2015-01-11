#if !defined(CW_INCLUDE_STD_STRING_BYTE_MEMMOVE)
#define CW_INCLUDE_STD_STRING_BYTE_MEMMOVE
namespace std {
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
#endif