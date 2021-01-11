#pragma once
#include "TestCase.hpp"

namespace Unit_Tests {
	class SendingTesting : public Unit_Tests::TestCase {
		void queueTesting();
		void sendMachineTesting();
	public:
		SendingTesting();
		void runTests();
	};
}