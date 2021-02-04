#pragma once
#include "TestCase.hpp"

namespace Unit_Tests {

	/* Unit tests for objects and object map
	*///
	class ObjectTesting : public Unit_Tests::TestCase {
	public:
		ObjectTesting();
		void runTests();
	
	private:
		void testingObjectMap();
		void testingObjects();
		void testingReflection(); 
	};
}