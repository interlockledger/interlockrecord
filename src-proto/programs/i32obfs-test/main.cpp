
#include "I32Obfuscator.h"
#include <cstdio>
#include <ctime>

int main(int argc, char ** argv) {
	I32FeistelObfuscator o(clock());

	std::printf("This program performs a full test of the I32FeistelObfuscator. It takes a few time to run...\n");

	#pragma omp parallel
	std::printf("Thread!\n");

	#pragma omp parallel for
	for (uint32_t v = 0; v < 0xFFFFFFFF; v++) {
		std::uint32_t p = o.obfuscate(v);
		if (o.deobfuscate(p) != v) {
			printf("Ooops!");
		}
	}
	std::uint32_t p = o.obfuscate(0xFFFFFFFF);
	if (o.deobfuscate(p) != 0xFFFFFFFF) {
		printf("Ooops!");
	}

	std::printf("Done!\n");
	return 0;
}

