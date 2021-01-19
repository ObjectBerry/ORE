#pragma once
#include "TestCase.hpp"

namespace Unit_Tests {
	class CompilerTesting : public Unit_Tests::TestCase {
		void testingByteTranslator();
	public:
		CompilerTesting();
		void runTests();
	};
}