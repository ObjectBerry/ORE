#pragma once
#include "TestCase.hpp"

namespace Unit_Tests {
	class InterpreterTesting : public Unit_Tests::TestCase {
	public:
		InterpreterTesting();
		void runTests();
	};
}