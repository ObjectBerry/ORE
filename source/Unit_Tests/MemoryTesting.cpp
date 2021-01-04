#include "../Memory/MemorySpace.hpp"

#include "MemoryTesting.hpp"

Unit_Tests::MemoryTesting::MemoryTesting() : TestCase("Memory testing") {};


void Unit_Tests::MemoryTesting::runTests() {
	// Memory Space testing
	Memory::MemorySpace* memSpace = new Memory::MemorySpace(32);
	char* buffer = memSpace->getBuffer();

	// One byte allocation
	char* oneByte = static_cast<char*>( memSpace->allocateMemory(1));
	*(oneByte) = 10;
	
	DO_CHECK("Memory Space: one byte allocation", *(oneByte) == buffer[0]);
	
	// Int allocation (4 bytes)
	int* numb = static_cast<int*>(memSpace->allocateMemory(sizeof(int)));
	*(numb) = 0x11223344;
	int* bufferInt = reinterpret_cast<int*>(buffer + 1);
	DO_CHECK("Memory Space: four bytes allocation", *(numb) == *(bufferInt));



	// Allocation from backward
	int* numb2 = static_cast<int*>(memSpace->allocateMemory(sizeof(int), true));
	*(numb) = 0x11223344;
	
	int* bufferInt2 = reinterpret_cast<int*>(buffer + 28);
	DO_CHECK("Memory Space: backward allocation", *(numb2) == *(bufferInt2));

	// Testing fullness
	// we will just allocate fat object
	char* ptr = static_cast<char*>( memSpace->allocateMemory(1000));
	DO_CHECK("Memory Space: fullness tesing", ptr == nullptr);


	// Testing buffer reseting
	memSpace->resetBuffer();
	bool res = true;
	for (unsigned i = 0; i < memSpace->getBufferSize(); i++) {
		if (buffer[i] != 0x00) {
			res = false;
			break;
		}
	}

	DO_CHECK("Memory Space: Reseting", res);

	delete memSpace;
}