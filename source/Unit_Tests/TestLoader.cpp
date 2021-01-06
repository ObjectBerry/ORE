#include "ObjectTesting.hpp"
#include "MemoryTesting.hpp"
#include "InterpreterTesting.hpp"

#include "TestLoader.hpp"

void Unit_Tests::start() {
	delete ((new ObjectTesting)->start());
	delete ((new MemoryTesting)->start()); 
	delete ((new InterpreterTesting)->start());
}