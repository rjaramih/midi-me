#ifndef PLUGIN_DLLMANAGER_H
#define PLUGIN_DLLMANAGER_H

// Includes
#include "global.h"
#include <map>

namespace plugin
{
	// Forward declarations
	class DynamicLibrary;

	/**
		This class is used to load/unload and manage dynamic libraries.
		Use this class if you want to load or unload dynamic libraries,
		as it makes sure that the libraries aren't loaded twice.
	*/
	class PLUGINSYSTEM_API DllManager
	{
	protected:
		// Typedefs
		typedef std::map<string, DynamicLibrary *> LibraryMap;

		// Member variables
		LibraryMap m_libraries; //!< A map containing the loaded dynamic libraries

	public:
		// Constructors and destructor
		DllManager();
		virtual ~DllManager();

		// Load / unload functions
		DynamicLibrary *loadLibrary(const string &filename);
		void unloadLibrary(const string &filename);
		bool isLoaded(const string &filename) const;
		void unloadLibraries();

		// Other functions
		void *getSymbol(const string &library, const string &symbol) throw();
		string getLastError() const;

	private:
		// Private functions
		void clear();
	};
}

#endif // PLUGIN_DLLMANAGER_H
