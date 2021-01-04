#include "ObjectTesting.hpp"

#include "TestLoader.hpp"

void Unit_Tests::start() {
	delete ((new ObjectTesting)->start());
}