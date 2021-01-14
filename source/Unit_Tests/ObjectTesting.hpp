#pragma once
#include "TestCase.hpp"

namespace Unit_Tests {

	/* Unit tests for objects and object map
	*///
	class ObjectTesting : public Unit_Tests::TestCase {
		void testingObjectMap();
		void testingObjects();
		void testingObjectFactory();
	public:
		ObjectTesting();
		void runTests();
	};
}