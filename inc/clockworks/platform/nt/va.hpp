#if !defined(CW_INCL_PLATFORM_NT_VA)
#define CW_INCL_PLATFORM_NT_VA
namespace ClockWorks {
	namespace OS {
		namespace Win32 {
			typedef char* va_list;
#			if defined(__clang__)
#				define 	va_start(ap, param)   __builtin_va_start(ap, param)
#				define 	va_end(ap)   __builtin_va_end(ap)
#				define 	va_arg(ap, type)   __builtin_va_arg(ap, type)
#				define 	__va_copy(d, s)   __builtin_va_copy(d,s)
#				define 	va_copy(dest, src)   __builtin_va_copy(dest, src)
#			elif defined(_MSC_VER)
				// All of this is untested, but taken almost verbatim from MSVC headers
#				if defined(CW_ARCH_X86)
#					define va_start(ap, v)	((void)(ap =\
						(va_list)(&const_cast<char&>(reinterpret_cast<const volatile char&>(v)))\
						+ ((sizeof(v) + sizeof(int) - 1) & ~(sizeof(int) - 1))))
#					define va_arg(ap, t)		(*(t*)((ap +=\
						((sizeof(t) + sizeof(int) - 1) & ~(sizeof(int) - 1)))\
						- ((sizeof(t) + sizeof(int) - 1) & ~(sizeof(int) - 1))))
#						define va_end(ap)			((void)(ap = (va_list)0))
#				elif  defined(CW_ARCH_X64)
					void __cdecl __va_start(va_list* , ...);
#					define va_start(ap, x)	((void)(__va_start(&ap, x)))
#					define va_arg(ap, t)	((sizeof(t) > sizeof(__int64)\
						|| (sizeof(t) & (sizeof(t) - 1)) != 0)\
						? **(t**)((ap += sizeof(__int64)) - sizeof(__int64))\
						:  *(t* )((ap += sizeof(__int64)) - sizeof(__int64)))
#					define va_end(ap)		((void)(ap = (va_list)0))
#				else
#					error Unsupported arch.
#				endif
#			else
#				error Unsupported compiler.
#			endif
		}
	}
}
#endif