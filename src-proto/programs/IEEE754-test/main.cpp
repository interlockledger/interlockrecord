
#include <string>
#include <cstdint>
#include <iostream>
using namespace std;

const string & toBits(const void * buff, int buffSize, string & out) {
	const uint8_t * p;
	const uint8_t * pEnd;

	p = (const uint8_t *)buff;
	pEnd = p + buffSize;

	for (; p < pEnd; p++) {
		for (int i = 0; i < 8; i++) {
			if (((*p) << i) & 0x80) {
				out.push_back('1');
			} else {
				out.push_back('0');
			}
		}
		out.push_back(' ');
	}
	return out;
}


int main() {
	string s;
	uint8_t v;
	union {
		float f;
		uint32_t i;
	} f;


	v = 0xA5;
	cout << toBits(&v, 1, s) << "\n";

	f.f = 3.1415927410;
	s.clear();
	cout << toBits(&f.f, sizeof(f), s) << "\n";

	s.clear();
	cout << toBits(&f.i, sizeof(f), s) << "\n";

	return 0;
}
