#include <gtest/gtest.h>
#include <iostream>

int main(int argc, char **argv) {
	int retval; 
	std::cout << "Running main() from gtest_main.cc\n";

	testing::InitGoogleTest(&argc, argv);

	retval = RUN_ALL_TESTS();

	return retval;
}
 