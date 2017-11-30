
#include <vector>
#include <cstdint>
#include <botan/build.h>
#include <botan/sha2_32.h>
#include <iostream>
#include <cstdio>

int main(int argc, char ** argv) {

	Botan::SHA_256 hash;
	std::vector<Botan::byte> output;

	hash.final(output);
	//std::cout << output.size(); 
	for (int i = 0; i < output.size(); i++) {
		std::printf("%02X ", output.at(i));
	}
	return 0;
}

