 #if !defined(CW_INCL_STD_STRING_BYTE_ITOA)
#define CW_INCL_STD_STRING_BYTE_ITOA

namespace std {
	int itoa(int value, char *sp, int radix = 10) {
		char tmp[34] = {0};
		char *tp = tmp;
		int i;
		unsigned v;
		int sign = (radix == 10 && value < 0);    
		if (sign){v = -value;} else {v = (unsigned)value;}
		while (v || tp == tmp) {
			i = v % radix;
			v /= radix;
			if (i < 10){*tp++ = i+'0';} else {*tp++ = i + 'A' - 10;}
		}
		
		int len = tp - tmp;

		if (sign){
			*sp++ = '-';
			len++;
		}

		while (tp > tmp){*sp++ = *--tp;}
		*sp++ = '\0';
		return len;
	}
}

#endif