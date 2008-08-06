#ifndef PLUGINSYSTEM_GLOBAL_H
#define PLUGINSYSTEM_GLOBAL_H

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
	#define _WIN32_WINNT 0x0502
	#include <windows.h>

	// Windows dll defines
	#if defined(PLUGINSYSTEM_EXPORTING) // Creating a dynamic library
		#define PLUGINSYSTEM_API __declspec(dllexport)
	#elif defined(PLUGINSYSTEM_STATIC) // Creating or using a static library
		#define PLUGINSYSTEM_API
	#else // Using the dynamic lib
		#define PLUGINSYSTEM_API __declspec(dllimport)
	#endif

	// Windows plugin defines
	#define PLUGIN_API extern "C" __declspec(dllexport)

// Linux, Mac OS, ...
#else
	// Make compatible with the windows function
	#define stricmp strcasecmp

	// No dll export macro needed
	#define PLUGINSYSTEM_API

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

#ifndef _PSP
	using std::wstring;
	using std::wcout;
	using std::wcin;
	using std::wcerr;
#endif

#include <cassert>


// Defines
#ifndef NULL
	#define NULL 0
#endif // NULL


#endif // PLUGINSYSTEM_GLOBAL_H
