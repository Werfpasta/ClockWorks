/******************************************************************
 * This file is the os definitions file for the WerfPasta stdlib. *
 ******************************************************************/

#if !defined(CW_INCLUDE_OS)
#define CW_INCLUDE_OS

// DESKTOP DEFINES

// WINDOWS STUPHS
#	if !defined(CW_INCLUDE_WINDOWS)
#		if defined(_WIN32)
#			define CW_INCLUDE_WINDOWS
#			define WIN32_LEAN_AND_MEAN
#			define VC_EXTRALEAN
#			include <Windows.h>
#		endif
#	endif

// LINUX STUPHS
#	if !defined(__ANDROID__)
#		if defined(__linux__)
#			if !defined(CW_INCLUDE_LINUX)
#				define CW_INCLUDE_LINUX
#				include <linux.h>
#			endif
#		endif
#	endif

// SOLARIS STUPHS
#	if defined(__sun)
#		if !defined(CW_INCLUDE_SUN)
#			define CW_INCLUDE_SUN
// why solaris, do I have to use the stdlib with you!?  :'(
#		endif
#	endif

// MAC OS X STUPHS


// BSD STUPHS (OH GOD PLEASE HALP!!!)


// MINIX STUPHS (Will this even work???  If not, we know what OS we have to work on...)



// MOBILE DEFINES

// ANDROID STUPHS
#	if defined(__ANDROID__)
#		if !defined(CW_INCLUDE_ANDROID)
#			define CW_INCLUDE_ANDROID
#			include <android/api-level.h>
#		endif
#	endif

#endif
