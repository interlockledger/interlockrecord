
#include "dlltest_t.h"
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <string>
#include <unistd.h>
#include "CLibrary.h"

int main(int argc, char ** argv) {
	char currdir[1024];
	CLibrary library;

	if (getcwd(currdir, sizeof(currdir)) == NULL) {
		std::cout << "Unable to get the current directory.\n";
		return 1;
	}
	std::string fullpath(currdir);
	fullpath += "/libdlltest.so";
	std::cout << "Current library: " << fullpath << "\n";

	if (!library.load(fullpath.c_str())){
		std::cout << "Unable to load the library.\n";
		//std::cout << dlerror() << "\n";
		return 1;
	}

	function_a_t f = (function_a_t) library.findFunction("function_a");
	if (!f){
		std::cout << "Unable to find the function function_a.\n";
		//std::cout << dlerror() << "\n";
		return 1;
	}

	return 0;
}

