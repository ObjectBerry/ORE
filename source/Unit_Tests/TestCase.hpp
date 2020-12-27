#pragma once

#define DO_CHECK(checkName, calculation) this->doCheck(checkName, calculation, __LINE__)
namespace Unit_Tests {
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