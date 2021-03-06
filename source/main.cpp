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

#include "Runtime/Metaverse.hpp"


int main(int argc, char** argv) {
	Runtime::Metaverse* metaverse = Runtime::Metaverse::create();
	metaverse->initialize(argc, argv);
	metaverse->start();
	
	delete metaverse;
	/*
	Runtime::initializeVM(argc, argv);
	Runtime::start();
	*/
	return 0;
}
#endif