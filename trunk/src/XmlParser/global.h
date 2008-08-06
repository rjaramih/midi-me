#ifndef XMLPARSER_GLOBAL_H
#define XMLPARSER_GLOBAL_H

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

	#define _CRT_SECURE_NO_DEPRECATE
	#define WIN32_LEAN_AND_MEAN
	#include <windows.h>

	// Windows dll defines
	#if defined(XMLPARSER_EXPORTING) // Creating a dynamic library
		#define XMLPARSER_API __declspec(dllexport)
	#elif defined(XMLPARSER_STATIC) // Creating or using a static library
		#define XMLPARSER_API
	#else // Using the dynamic lib
		#define XMLPARSER_API __declspec(dllimport)
	#endif

	// Windows plugin defines
	#define XMLPARSER_PLUGIN extern "C" __declspec(dllexport)

// Linux, Mac OS, ...
#else
	// Make compatible with the windows function
	#define stricmp strcasecmp

	// No dll export macro needed
	#define XMLPARSER_API

	// Plugin defines
	#define XMLPARSER_PLUGIN extern "C"
#endif


#include <string>
using std::string;
using std::wstring;

/*
#include <iostream>
using std::cout;
using std::wcout;
using std::cin;
using std::wcin;
using std::cerr;
using std::wcerr;
using std::endl;
*/

#include <stdio.h>
#include <cassert>


// Defines
#ifndef NULL
	#define NULL 0
#endif // NULL


#endif // XMLPARSER_GLOBAL_H
