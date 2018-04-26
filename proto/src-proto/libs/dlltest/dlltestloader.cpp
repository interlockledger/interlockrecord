
#include "dlltest_t.h"
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <string>
#ifdef _WIN32
	#include <windows.h>
#else
	#include <unistd.h>
#endif //_WIN32
#include "IRLibrary.h"

int main(int argc, char ** argv) {
	char currdir[1024];
	IRLibrary library;

#ifdef _WIN32
	if (GetCurrentDirectory(sizeof(currdir), currdir) == 0) {
		std::cout << "Unable to get the current directory.\n";
		return 1;
	}
#else
	if (getcwd(currdir, sizeof(currdir)) == NULL) {
		std::cout << "Unable to get the current directory.\n";
		return 1;
	}
#endif //_WIN32
	std::string fullpath(currdir);
#ifdef _WIN32
	fullpath += "\\";
#else
	fullpath += "/";
#endif //_WIN32
	std::string file;
	IRLibrary::getLibraryFile("dlltest", file);
	fullpath += file;

	std::cout << "Current library: " << fullpath << "\n";
	if (!library.load(fullpath.c_str())){
		std::cout << "Unable to load the library.\n";
		std::cout << "Error: " << library.error() << "\n";
		return 1;
	} else {
		std::cout << "Library loaded.\n";
	}

	function_a_t f = (function_a_t) library.findSymbol("function_a");
	if (!f){
		std::cout << "Unable to find the function function_a.\n";
		std::cout << "Error: " << library.error() << "\n";
		return 1;
	} else {
		std::cout << "function_a found.\n";
	}

	if (!library.unload()) {
		std::cout << "Unable to uload the library.\n";
		std::cout << "Error: " << library.error() << "\n";
		return 1;
	} else {
		std::cout << "Library unloaded.\n";
	}
	
	return 0;
}

