#pragma once

#define DO_CHECK(checkName, calculation) this->doCheck(checkName, calculation, __LINE__)
namespace Unit_Tests {
	
	/* This is basic test case used in unit testing
	// It have own name and it can count number of checks and number of failed checks
	// If you want use this class , inherit it and do 2 things:
	//  1) Pass Case name in constructor to parent class
	//  2) Override void runTests()
	*///
	class TestCase {
		char* _caseName;

		unsigned char _checks;
		unsigned char _failures;

	public:
		TestCase(const char* caseName);

	protected:
		void			doCheck(const char* checkName, bool calculation, int line);
		void			printStatus();
		virtual void	runTests() = 0;

	public:
		void			start();
	};
}