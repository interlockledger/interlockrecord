
#include "dlltest.h"

extern "C" {

IR_EXPORT_ATTR int IR_EXPORT_CALL function_a(int a) {
	return a;
}

int function_b(int a) {
	return a;
}

} //extern "C"

