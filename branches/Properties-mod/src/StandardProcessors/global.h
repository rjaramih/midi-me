#ifndef STANDARDPROCESSORS_GLOBAL_H
#define STANDARDPROCESSORS_GLOBAL_H

// Includes

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif


// Windows and pocket pc
#if defined(_WIN32_WCE) || defined(WIN32)
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
	#if defined(STANDARDPROCESSORS_EXPORTING) // Creating a dynamic library
		#define STANDARDPROCESSORS_API __declspec(dllexport)
	#elif defined(STANDARDPROCESSORS_STATIC) // Creating or using a static library
		#define STANDARDPROCESSORS_API
	#else // Using the dynamic lib
		#define STANDARDPROCESSORS_API __declspec(dllimport)
	#endif

	// Windows plugin defines
	#define PLUGIN_API extern "C" __declspec(dllexport)

// Linux, Mac OS, ...
#else
	// Make compatible with the windows function
	#define stricmp strcasecmp

	// No dll export macro needed
	#define STANDARDPROCESSORS_API

	// Plugin defines
	#define PLUGIN_API extern "C"
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


#endif // STANDARDPROCESSORS_GLOBAL_H
