#include <stdio.h>

//------------------------------------------------------------------------------
// Reference code extracted from https://en.wikipedia.org/wiki/Xorshift
#include <stdint.h>

/* The state must be seeded so that it is not all zero */
uint64_t s[2];

uint64_t xorshift128plus(void) {
	uint64_t x = s[0];
	uint64_t const y = s[1];
	s[0] = y;
	x ^= x << 23; // a
	s[1] = x ^ y ^ (x >> 17) ^ (y >> 26); // b, c
	return s[1] + y;
}

//------------------------------------------------------------------------------
int main() {
	s[0] = 0xf5539d6bc442958ell;
	s[1] = 0x4b0bdbb42366c4a6ll;

	for (int i = 0; i < 8; i++) {
		printf("0x%lXll, 0x%lXll,\n", xorshift128plus(), xorshift128plus());
	}
	return 0;
}
