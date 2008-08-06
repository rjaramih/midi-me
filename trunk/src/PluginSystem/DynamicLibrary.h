#ifndef PLUGIN_DYNAMICLIBRARY_H
#define PLUGIN_DYNAMICLIBRARY_H

// Includes
#include "global.h"

#ifdef _PSP_
	#include <pspkernel.h>
#endif

namespace plugin
{
	// Typedefs
	#if defined(_WIN32_WCE) || defined(WIN32)
		typedef HINSTANCE__ * DLHandle;
	#elif defined(__unix__) || defined(__APPLE__)
		typedef void * DLHandle;
	#elif defined(_PSP_)
		typedef SceUID DLHandle;
	#else
		#error "This class can't be used for this system"
	#endif

	typedef void (*SimpleFunction)(void); //!< A simple function pointer (no parameters or return value)

	/**
		This class represents a dynamic library that can be loaded
		at runtime. The user won't use this class directly, but through the DllManager
		(or implicitly through the PluginManager).

		To ease resolving simple functions (withouth return type of parameters),
		a typedef is created for these: SimpleFunction.

		@todo
			- Mac dynamic libraries aren't handled. Maybe implement different classes
			  for each architecture (LinuxDynamicLibrary, WindowsDynamicLibrary, ...)?
			- Add a search path?
	*/
	class PLUGINSYSTEM_API DynamicLibrary
	{
	protected:
		// Member variables
		string m_filename;
		DLHandle m_handle;

	public:
		// Constructors and destructor
		DynamicLibrary(const string &filename);
		virtual ~DynamicLibrary();

		// Get functions
		//! Gets the fully qualified filename (with the right prefix and extension added)
		const string &getFilename() const { return m_filename; }

		// Load / unload functions
		bool load();
		bool unload();
		bool isLoaded() const { return (m_handle != 0); }

		// Other functions
		void *getSymbol(const string &name) throw();
		static void *getSymbol(const string &library, const string &symbol) throw();

		void startFunction(const string &name) throw();
		static void startFunction(const string &library, const string &function) throw();

		static string getLastError();
		static void correctFilename(string &filename);

	private:
		// Private functions
		void correctFilename() { correctFilename(m_filename); }
	};
}

#endif // PLUGIN_DYNAMICLIBRARY_H
