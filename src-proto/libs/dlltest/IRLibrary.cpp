
#include "IRLibrary.h"
#ifndef __WIN32__
	#include <dlfcn.h>
#endif //__WIN32__
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
#ifdef __WIN32__
		char tmp[16]; // It will hold a string with at most 11 digits
		DWORD errorCode = GetLastError();
		std::snprintf(tmp, sizeof(tmp), "0x%08X", errorCode);
		this->_error = tmp;
#else
		this->_error = dlerror();
#endif //__WIN32__
}

//------------------------------------------------------------------------------
bool IRLibrary::load(const char * path) {

	if (this->isLoaded()) {
		return true;
	}

	this->_path = path;
#ifdef __WIN32__
	this->_handle = LoadLibrary(path);
#else
	this->_handle = dlopen(this->_path.c_str(), RTLD_LAZY);
#endif //__WIN32__
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
#ifdef __WIN32__
		bool result = (FreeLibrary(this->_handle) != 0);
#else
		bool result = (dlclose(this->_handle) != 0);
#endif //__WIN32__
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
#ifdef __WIN32__
		return GetProcAddress(this->handle(), name);
#else
		return dlsym(this->handle(), name);
#endif //__WIN32__
	} else {
		return NULL;
	}
}
//------------------------------------------------------------------------------

