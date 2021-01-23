// TODO: probably refactor this macros into different files
#define TESTING false

#if TESTING == true 
// Branch for testing

#include "Unit_Tests/TestLoader.hpp"
int main() {
	Unit_Tests::start();
	return 0;
}

#else
// Branch for release

#include "Runtime/Initialization.hpp"


int main(int argc, char** argv) {
	Runtime::initializeVM(argc, argv);
	Runtime::start();
	return 0;
}
#endif