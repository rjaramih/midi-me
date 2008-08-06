// Includes
#include "DllManager.h"
#include "DynamicLibrary.h"
using namespace plugin;


/******************************
* Constructors and destructor *
******************************/

DllManager::DllManager()
{
}

//! @todo Unload libraries here? Or only at application exit, unless explicitly called?
DllManager::~DllManager()
{
	clear();
}


/**************************
* Load / unload functions *
**************************/

/*! Get a dynamic library. The library is loaded if necessary. */
DynamicLibrary *DllManager::loadLibrary(const string &filename)
{
	// Correct the filename (add the correct prefix and extension if necesarry)
	string realname = filename;
	DynamicLibrary::correctFilename(realname);

	// Check if the library is already loaded
	LibraryMap::const_iterator it = m_libraries.find(realname);
	if(it != m_libraries.end())
		return it->second;

	// Load and map the library
	DynamicLibrary *pLib = new DynamicLibrary(realname);
	if(!pLib->isLoaded())
	{
		delete pLib;
		return 0;
	}

	m_libraries[realname] = pLib;
	return pLib;
}

/*! Unload a dynamic library. */
void DllManager::unloadLibrary(const string &filename)
{
	// Correct the filename (add the correct prefix and extension if necesarry)
	string realname = filename;
	DynamicLibrary::correctFilename(realname);

	// Check if the library is loaded
	LibraryMap::iterator it = m_libraries.find(realname);
	if(it != m_libraries.end())
	{
		delete it->second;
		m_libraries.erase(it);
	}
}

/*! Checks if a library is loaded */
bool DllManager::isLoaded(const string &filename) const
{
	// Correct the filename (add the correct prefix and extension if necesarry)
	string realname = filename;
	DynamicLibrary::correctFilename(realname);

	LibraryMap::const_iterator it = m_libraries.find(realname);
	return it != m_libraries.end();
}

/*! Unload all the dynamic libraries */
void DllManager::unloadLibraries()
{
	/*! @todo
		As being constructed and being loaded is the same for now,
		this is essentially the same as clear().
	*/
	clear();
}


/******************
* Other functions *
******************/

/*! Convenience function: gets a symbol from a certain library.
	The library is loaded if necesarry.
	@param library The filename of the library
	@param symbol The name of the exported symbol you want to resolve.
	@return A pointer to the resolved symbol. 0 if the library couldn't be loaded, or the symbol isn't exported.
*/
void *DllManager::getSymbol(const string &library, const string &symbol) throw()
{
	DynamicLibrary *pLib = loadLibrary(library);
	return pLib->getSymbol(symbol);
}

/*! Convenience function: same as DynamicLibrary::getLastError(). */
string DllManager::getLastError() const
{
	return DynamicLibrary::getLastError();
}


/********************
* Private functions *
********************/

/*! Delete all the libraries from the manager. */
void DllManager::clear()
{
	LibraryMap::iterator it;
	for(it = m_libraries.begin(); it != m_libraries.end(); ++it)
		delete it->second;
	m_libraries.clear();
}
