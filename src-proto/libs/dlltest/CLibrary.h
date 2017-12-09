
#ifndef __CLibrary_H__
#define __CLibrary_H__

#include <string>

class CLibrary {
private:
	std::string _path;
	
	void * _handle;

public:
	CLibrary();

	virtual ~CLibrary();

	bool load(const char * path);
	
	bool unload();

	void * findFunction(const char * name);

	bool isLoaded() const {
		return (this->handle() != NULL);
	}

	const std::string & path() const {
		return this->_path;
	}

	const void * handle() const {
		return this->_handle;
	}

	void * handle() {
		return this->_handle;
	}
};

#endif //__CLibrary_H__

