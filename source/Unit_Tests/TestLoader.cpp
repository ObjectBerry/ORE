#include "ObjectTesting.hpp"
#include "MemoryTesting.hpp"

#include "TestLoader.hpp"

void Unit_Tests::start() {
	delete ((new ObjectTesting)->start());
	delete ((new MemoryTesting)->start()); 
}