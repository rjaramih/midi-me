// Includes
#include "DynamicLibrary.h"
#include "StringUtil.h"
using namespace plugin;
using namespace MidiMe;

#if defined(__unix__) || defined(__APPLE__)
	#include <dlfcn.h>
#endif // __unix__


/******************************
* Constructors and destructor *
******************************/

/*! Constructs a dynamic library. The library gets loaded automatically.

	@param filename
		The filename of the dynamic library you want to load.
		It is best to not include the file extention, as that is more portable.
		The correct prefix (eg. "lib" in linux) and file extension (eg. ".so")
		is added automatically, depending on which platform you're using this class.
*/
DynamicLibrary::DynamicLibrary(const string &filename)
: m_filename(filename), m_handle(0)
{
	correctFilename();
	load();
}

/*! Unloads and destructs a dynamic library. */
DynamicLibrary::~DynamicLibrary()
{
	//! @todo Do we have to unload here? QT just waits till the application stops
	unload();
}


/******************
* Other functions *
******************/

#ifdef _PSP_
SceUID load_module(const char *path, int flags, int type)
{
	SceKernelLMOption option;
	SceUID mpid;

	/* If the type is 0, then load the module in the kernel partition, otherwise load it
	   in the user partition. */
	if (type == 0) {
		mpid = 1;
	} else {
		mpid = 2;
	}

	memset(&option, 0, sizeof(option));
	option.size = sizeof(option);
	option.mpidtext = mpid;
	option.mpiddata = mpid;
	option.position = 0;
	option.access = 1;

	return sceKernelLoadModule(path, flags, type > 0 ? &option : NULL);
}
#endif

/*! Loads the library.
	@return True if the loading was a succes. False otherwise.
	@todo Handle ascii/unicode better
*/
bool DynamicLibrary::load()
{
	// Only load once
	if(isLoaded()) return true;

#if defined(_WIN32_WCE)
	m_handle = (DLHandle) LoadLibrary(StringUtil::toUnicode(m_filename).c_str());
#elif defined(WIN32)
	m_handle = (DLHandle) LoadLibraryEx(StringUtil::toUnicode(m_filename).c_str(), NULL, LOAD_WITH_ALTERED_SEARCH_PATH);
	//m_handle = (DLHandle) LoadLibrary(StringUtil::toUnicode(m_filename).c_str());
#elif defined(__unix__) || defined(__APPLE__)
	m_handle = (DLHandle) dlopen(m_filename.c_str(), RTLD_NOW);
#elif defined(_PSP_)
	m_handle = load_module(m_filename.c_str(), 0, 0);
#endif

	return (m_handle != 0);
}

/*! Unloads the library.
	@return True if the unloading was a success. False otherwise.
*/
bool DynamicLibrary::unload()
{
	// Only unload once
	if(!isLoaded()) return true;

	bool success = false;

#if defined(_WIN32_WCE)
	//! @todo Enable this again, when the crashing is gone...
	//success = (FreeLibrary(m_handle) != 0);
#elif defined(WIN32)
	success = (FreeLibrary(m_handle) != 0);
#elif defined(__unix__) || defined(__APPLE__)
	success = (dlclose(m_handle) == 0);
#elif defined(_PSP_)
	int status;
	success = sceKernelStopModule(m_handle, 0, 0, &status, 0);
	success = sceKernelUnloadModule(m_handle);
#endif

	m_handle = 0;

	return success;
}

/*! Gets a symbol from the library. The library is loaded if it isn't yet.
	@param name The name of the exported symbol you want to resolve.
	@return A pointer to the resolved symbol. 0 If the library couldn't be loaded, or the symbol isn't exported.
	@todo Handle ascii/unicode better
*/
void *DynamicLibrary::getSymbol(const string &name) throw()
{
	if(!isLoaded() && !load())
		return 0;

#if defined(_WIN32_WCE)
	return (void *) GetProcAddress(m_handle, StringUtil::toUnicode(name).c_str());
#elif defined(WIN32)
	return (void *) GetProcAddress(m_handle, name.c_str());
#elif defined(__unix__) || defined(__APPLE__)
	return (void *) dlsym(m_handle, name.c_str());
#elif defined(_PSP_)
	return 0;
#endif
}

/*! Starts a simple function from the library (without parameters or return value). The library is loaded if it isn't yet.
	@param name The name of the exported function you want to start.
*/
void DynamicLibrary::startFunction(const string &name) throw()
{
	SimpleFunction func = (SimpleFunction) getSymbol(name);
	if(func)
		func();
}

/*! Get the last error that occured.
	@todo Get Error messages in Windows
*/
string DynamicLibrary::getLastError()
{
#if defined(_WIN32_WCE) || defined(WIN32) || defined(_PSP_)
		return "No error information";
#elif defined(__unix__) || defined(__APPLE__)
		return dlerror();
#endif
}

/*! Convenience function: Load a library and get a symbol from it.
	@todo Should we unload the library. Even at destruction? In QT, they don't.
*/
void *DynamicLibrary::getSymbol(const string &library, const string &symbol) throw()
{
	DynamicLibrary lib(library);
	return lib.getSymbol(symbol);
}

/*! Convenience function: Load a library and start a simple exported function from it (without parameters or return value).
	@todo Should we unload the library. Even at destruction? In QT, they don't.
*/
void DynamicLibrary::startFunction(const string &library, const string &function) throw()
{
	DynamicLibrary lib(library);
	lib.startFunction(function);
}

/*! Checks a filename, and adds system-dependent pre- and suffixes if necesarry.
	For now, it just adds .dll in windows and .so in linux
	@todo Better checking of the filename (ignore version numbers at the end in linux, add lib in linux, ...)
*/
void DynamicLibrary::correctFilename(string &filename)
{
#if defined(_WIN32_WCE) || defined(WIN32)
	if(StringUtil::endsWith(filename, ".exe") || StringUtil::endsWith(filename, ".dll"))
		return;

	filename += ".dll";
#elif defined(__unix__)
	if(!StringUtil::endsWith(filename, ".so"))
		filename += ".so";

	string path = StringUtil::getFilePath(filename);
	string name = StringUtil::getFileName(filename);
	if(!StringUtil::startsWith(name, "lib"))
		name.insert(0, "lib");
	filename = path + name;
#elif defined(_PSP_)
	if(!StringUtil::endsWith(filename, ".prx"))
		filename += ".prx";

	string path = StringUtil::getFilePath(filename);
	string name = StringUtil::getFileName(filename);
	if(!StringUtil::startsWith(name, "lib"))
		name.insert(0, "lib");
	filename = path + name;
#elif defined(__APPLE__)
	if(!StringUtil::endsWith(filename, ".dylib"))
		filename += ".dylib";

	string path = "/usr/local/lib/";//StringUtil::getFilePath(filename);
	string name = StringUtil::getFileName(filename);
	if(!StringUtil::startsWith(name, "lib"))
		name.insert(0, "lib");
	filename = path + name;
#endif
}
