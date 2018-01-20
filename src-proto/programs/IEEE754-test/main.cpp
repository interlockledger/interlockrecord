
#include <string>
#include <cstdint>
#include <iostream>
using namespace std;

#define FLOAT_PI 3.1415927410f
const static std::uint8_t FLOAT_PI_BIN[4] = {0x40, 0x49, 0x0f, 0xdb};

bool IsBigEndian(){
	float f;
	std::uint8_t * b;
	b = (std::uint8_t *)&f;
	b[0] = 0x40;
	b[1] = 0x49;
	b[2] = 0x0f;
	b[3] = 0xdb;
	return f == FLOAT_PI;
}

bool IsLittleEndian(){
	float f;
	std::uint8_t * b;
	b = (std::uint8_t *)&f;

	b[3] = 0x40;
	b[2] = 0x49;
	b[1] = 0x0f;
	b[0] = 0xdb;
	return f == FLOAT_PI;
}


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
		std::uint8_t b[4];
	} f;


	v = 0xA5;
	cout << toBits(&v, 1, s) << "\n";

	f.f = 3.1415927410;
	s.clear();
	cout << toBits(&f.f, sizeof(f), s) << "\n";

	s.clear();
	cout << toBits(f.b, sizeof(f), s) << "\n";

	cout << IsBigEndian() << "\n";
	cout << IsLittleEndian() << "\n";
	return 0;
}
