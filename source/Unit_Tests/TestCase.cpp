#include "TestCase.hpp"

#include <iostream>



Unit_Tests::TestCase::TestCase(const char* caseName) {
	this->_caseName = const_cast<char*>(caseName);
	this->_checks = 0;
	this->_failures = 0;
}



void Unit_Tests::TestCase::doCheck(const char* checkName, bool calculation, int line) {
	this->_checks++;

	unsigned length = 0;
	while (checkName[length] != '\0')
		length++;
	length++;

	std::cout << "  [ " << checkName << " ](" << line << "):: ";


	if (calculation) {
		std::cout << "SUCCESS" << std::endl;
	}
	else {
		this->_failures++;
		std::cout << "FAILURE" << std::endl;
	}

}
void Unit_Tests::TestCase::printStatus() {
	std::cout << '\n';

	std::cout << "  Checks::   " << (int)this->_checks << std::endl;
	std::cout << "  Failures:: " << (int)this->_failures << std::endl;

	float percentage = (static_cast<float>(this->_checks - this->_failures) / this->_checks) * 100;
	std::cout << "  Successfulnes: " << percentage << " %" << std::endl;
}


void Unit_Tests::TestCase::runTests() {
	// empty
}

void Unit_Tests::TestCase::start() {
	std::cout << "{ Test Case:: " << this->_caseName << " }" << std::endl;
	this->runTests();

	this->printStatus();
	std::cout << std::endl;
}