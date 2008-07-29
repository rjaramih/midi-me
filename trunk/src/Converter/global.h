#ifndef CONVERTER_GLOBAL_H
#define CONVERTER_GLOBAL_H

// Windows and pocket pc
#if defined(_WIN32_WCE) || defined(WIN32)
	// Non dll-interface class used as base for dll-interface class
	#pragma warning (disable: 4275)

	// 'sprintf': This function or variable may be unsafe.
	#pragma warning (disable: 4996)

	// Identifier was truncated to '255' characters in the debug information
	#pragma warning (disable: 4786)

	// Conversion from 'size_t' to 'unsigned int', possible loss of data
	/*!
		@note In VS.NET 7.1, it seems that size_t of STL is defined as a int in stead of a unsigned int.
	*/
	#pragma warning (disable: 4267)

	#define WIN32_LEAN_AND_MEAN
	#include <windows.h>

// Linux, Mac OS, ...
#else
	// Window handle
	typedef size_t HWND;

	// Make compatible with the windows function
	#define stricmp strcasecmp

#endif


#include <string>
using std::string;

#include <iostream>
using std::cout;
using std::cin;
using std::cerr;
using std::endl;

#include <cassert>


// Defines
#ifndef NULL
	#define NULL 0
#endif // NULL


#endif // CONVERTER_GLOBAL_H
