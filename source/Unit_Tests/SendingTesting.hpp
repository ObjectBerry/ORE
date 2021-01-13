#pragma once
#include "TestCase.hpp"

namespace Unit_Tests {
	class SendingTesting : public Unit_Tests::TestCase {
		void testingQueue();
		void testingSendMachine();
	public:
		SendingTesting();
		void runTests();
	};
}