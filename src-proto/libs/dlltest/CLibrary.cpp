
#include "CLibrary.h"
#include <dlfcn.h>

CLibrary::CLibrary():_path(), _handle(NULL){
}

CLibrary::~CLibrary() {
	this->unload();
}

bool CLibrary::load(const char * path) {

	if (this->isLoaded()) {
		return false;
	}
	this->_path = path;
	this->_handle = dlopen(this->_path.c_str(), RTLD_LAZY);
	return this->_handle;
}

bool CLibrary::unload() {

	if (this->isLoaded()) {
		if (dlclose(this->_handle)) {
			return false;
		} else {
			this->_handle = NULL;
			return true;
		}
	} else {
		return true;
	}
}

void * CLibrary::findFunction(const char * name) {

	if (this->isLoaded()) {
		return dlsym(this->handle(), name);
	} else {
		return NULL;
	}
}

