#pragma once
#include "TestCase.hpp"


namespace Unit_Tests {
	class RuntimeTesting : public Unit_Tests::TestCase {
	public:
		RuntimeTesting(); 
		void runTests();
	
	private:
		void testObjectUniverse();
	};
}