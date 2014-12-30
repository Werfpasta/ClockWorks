#if !defined(CW_INCLUDE_OS)
#	if defined(_WIN32)
#		define CW_OS_WIN
#		if defined(_WIN64)
#			define CW_OS_WIN64
#		else
#			define CW_OS_WIN32
#		endif
#	elif defined(__linux__)
#		if defined(__ANDROID__)
#			define CW_OS_ANDROID
#		else
#			define CW_OS_LINUX
#		endif
#	endif
#endif