#include "ObjectTesting.hpp"
#include "MemoryTesting.hpp"
#include "InterpreterTesting.hpp"
#include "SendingTesting.hpp"
#include "CompilerTesting.hpp"
#include "RuntimeTesting.hpp"

#include "TestLoader.hpp"

void Unit_Tests::start() {
	
	delete ((new ObjectTesting)->start());
	delete ((new MemoryTesting)->start()); 
	delete ((new InterpreterTesting)->start());
	delete ((new SendingTesting)->start()); 	
	delete ((new CompilerTesting)->start());
	delete ((new RuntimeTesting)->start());
}