
#include "IRLibrary.h"
#ifndef _WIN32
	#include <dlfcn.h>
#endif //__WIN32
#include <cstdio>

//==============================================================================
// Class IRLibrary
//------------------------------------------------------------------------------
IRLibrary::IRLibrary():_path(), _error(), _handle(NULL){
}

//------------------------------------------------------------------------------
IRLibrary::~IRLibrary() {
	this->unload();
}

//------------------------------------------------------------------------------
bool IRLibrary::postLoad() {
	return true;
}

//------------------------------------------------------------------------------
bool IRLibrary::postUnload() {
	return true;
}

//------------------------------------------------------------------------------
void IRLibrary::getErrorMessage() {
#ifdef _WIN32
		char tmp[16]; // It will hold a string with at most 11 digits
		DWORD errorCode = GetLastError();
		std::snprintf(tmp, sizeof(tmp), "0x%08X", errorCode);
		this->_error = tmp;
#else
		this->_error = dlerror();
#endif //_WIN32
}

//------------------------------------------------------------------------------
bool IRLibrary::load(const char * path) {

	if (this->isLoaded()) {
		return true;
	}

	this->_path = path;
#ifdef _WIN32
	this->_handle = LoadLibrary(path);
#else
	this->_handle = dlopen(this->_path.c_str(), RTLD_LAZY);
#endif //_WIN32
	if (this->_handle) {
		return this->postLoad();
	} else {
		this->getErrorMessage();
		return false;
	}
}

//------------------------------------------------------------------------------
bool IRLibrary::unload() {

	if (this->isLoaded()) {
#ifdef _WIN32
		bool result = (FreeLibrary(this->_handle) != 0);
#else
		bool result = (dlclose(this->_handle) != 0);
#endif //_WIN32
		if (result) {
			this->_handle = NULL;
			return this->postUnload();
		} else {
			this->getErrorMessage();
			return false;
		}
	} else {
		return true;
	}
}

//------------------------------------------------------------------------------
IRLibrary::symbol_addr_t IRLibrary::findSymbol(const char * name) {

	if (this->isLoaded()) {
#ifdef _WIN32
		return GetProcAddress(this->handle(), name);
#else
		return dlsym(this->handle(), name);
#endif //_WIN32
	} else {
		return NULL;
	}
}

//------------------------------------------------------------------------------
void IRLibrary::getLibraryFile(const char * title, std::string & filename) {
	
#if defined(_WIN32)
	filename = title;
	filename += ".dll";
#elif defined(__APPLE__)
	filename = title;
	filename += title;
	filename += ".dylib";
#else
	filename = "lib";
	filename += title;
	filename += ".so";
#endif //_WIN32
}
//------------------------------------------------------------------------------

