#ifndef LIBMIDIME_GLOBAL_H
#define LIBMIDIME_GLOBAL_H

// Windows and pocket pc
#if defined(_WIN32_WCE) || defined(WIN32)
	// Non dll-interface class used as base for dll-interface class
	#pragma warning (disable: 4275)

	// 'sprintf': This function or variable may be unsafe.
	#pragma warning (disable: 4996)

	// Identifier was truncated to '255' characters in the debug information
	#pragma warning (disable: 4786)

	// STL classes are not exported in the dll
	/*!
		@note This can be ignored, since none of the stl members are public,
		so they shouldn't be exported in the dll
	*/
	#pragma warning (disable: 4251)

	// Conversion from 'size_t' to 'unsigned int', possible loss of data
	/*!
		@note In VS.NET 7.1, it seems that size_t of STL is defined as a int in stead of a unsigned int.
	*/
	#pragma warning (disable: 4267)

	#define WIN32_LEAN_AND_MEAN
	#include <windows.h>

	// Windows dll defines
	#if defined(LIBMIDIME_EXPORTING) // Creating a dynamic library
		#define LIBMIDIME_API __declspec(dllexport)
	#elif defined(LIBMIDIME_STATIC) // Creating or using a static library
		#define LIBMIDIME_API
	#else // Using the dynamic lib
		#define LIBMIDIME_API __declspec(dllimport)
	#endif

	// Windows plugin defines
	#define PLUGIN_API extern "C" __declspec(dllexport)

// Linux, Mac OS, ...
#else
	// Window handle
	typedef size_t HWND;

	// Make compatible with the windows function
	#define stricmp strcasecmp

	// No dll export macro needed
	#define LIBMIDIME_API

	// Plugin defines
	#define PLUGIN_API extern "C"

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


#endif // LIBMIDIME_GLOBAL_H
