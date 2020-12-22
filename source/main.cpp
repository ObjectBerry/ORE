// TODO: probably refactor this macros into different files
#define TESTING true

#if TESTING == true 
// Branch for testing

#include "Unit_Tests/TestLoader.hpp"
int main() {
	Unit_Tests::start();
	return 0;
}

#else
// Branch for release
int main() {
	return 0;
}
#endif