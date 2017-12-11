
#ifndef __IRLibrary_H__
#define __IRLibrary_H__

#include <string>
#ifdef __WIN32__
	#include <windows.h>
#endif //__WIN32__

/**
 * This class implements a basic dynamic library abstraction.
 *
 * @author Fabio Jun Takada Chino (fchino at opencs.com.br)
 * @since 2017.12.09
 */
class IRLibrary {
public:
	/**
	 * Type of the library handle. The actual type may vary according to the platform.
	 */
	#ifdef __WIN32__
	typedef HMODULE handle_t;
	typedef FARPROC symbol_addr_t;
	#else
	typedef void * handle_t;
	typedef void * symbol_addr_t;
	#endif
private:
	/**
	 * The current library path.
	 */
	std::string _path;

	/**
	 * Error message if any.
	 */
	std::string _error;

	/**
	 * The library handle.
	 */
	handle_t _handle;

	void getErrorMessage();
protected:
	/**
	 * This method is called after the library is successfully loaded.
	 * It can be used to execute further initializations after the library
	 * is loaded. The default implementation does nothing.
	 *
	 * @return true on success or false otherwise.
	 */
	virtual bool postLoad();

	/**
	 * This method is called after the library is successfully unloaded.
	 * It can be used to execute further deinitializations after the library
	 * is unloaded. The default implementation does nothing.
	 *
	 * @return true on success or false otherwise.
	 */
	virtual bool postUnload();
public:
	/**
	 * Creates a new instance of this class. The library will not be loaded.
	 */
	IRLibrary();

	/**
	 * Disposes this instance and releases all associated resources.
	 */
	virtual ~IRLibrary();

	/**
	 * Loads the library from the given file.
	 *
	 * @param[in] path The path to the library.
	 * @return true on success or false otherwise.
	 * @note In case of error, the error message will be acquired using
	 * error() method.
	 * @note On success, this method calls postLoad() in order to allow
	 * further initialization procedures.
	 */
	bool load(const char * path);
	
	/**
	 * Unloads the library.
	 *
	 * @return true on success or false otherwise.
	 */
	bool unload();

	/**
	 * Finds a library symbol by name.
	 *
	 * @name The symbol name.
	 * 
	 */ 
	symbol_addr_t findSymbol(const char * name);

	bool isLoaded() const {
		return (this->handle() != NULL);
	}

	const std::string & path() const {
		return this->_path;
	}

	const std::string & error() const {
		return this->_error;
	}

	const handle_t handle() const {
		return this->_handle;
	}

	handle_t handle() {
		return this->_handle;
	}
};

#endif //__IRLibrary_H__

