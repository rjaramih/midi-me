#ifndef MIDIME_GLOBAL_H
#define MIDIME_GLOBAL_H

// Includes

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif


// Windows and pocket pc
#if defined(_WIN32_WCE) || defined(WIN32)
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
	// Make compatible with the windows function
	#define stricmp strcasecmp
#endif


#include <string>
using std::string;
using std::wstring;

#include <iostream>
using std::cout;
using std::wcout;
using std::cin;
using std::wcin;
using std::cerr;
using std::wcerr;
using std::endl;

#include <cassert>


// Defines
#ifndef NULL
	#define NULL 0
#endif // NULL


#endif // MIDIME_GLOBAL_H
