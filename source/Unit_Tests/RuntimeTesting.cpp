#include "../Memory/BufferAllocator.hpp"

#include "../Objects/Object.hpp"
#include "../Objects/String.hpp"

#include "../Runtime/ObjectUniverse.hpp"

#include "RuntimeTesting.hpp"

Unit_Tests::RuntimeTesting::RuntimeTesting() : Unit_Tests::RuntimeTesting::TestCase("Runtime") {}

void Unit_Tests::RuntimeTesting::runTests() {
	this->testObjectUniverse();
}


void Unit_Tests::RuntimeTesting::testObjectUniverse() {
	Memory::MemoryAllocator* basic, * tenured, * pernament;
	basic		= new Memory::BufferAllocator(2000);
	tenured		= new Memory::BufferAllocator(2000);
	pernament	= new Memory::BufferAllocator(100);

	Runtime::ObjectUniverse* objUniverse = new Runtime::ObjectUniverse(basic, tenured, pernament);
	objUniverse->genesis();  

	// Testing object creation
	Objects::ByteArray* byteArray = objUniverse->createByteArray(1); 
	Objects::String* string = objUniverse->createString("yo"); 

	DO_CHECK("Object Universe: System objects creation 1", (string->getObjectMap() == byteArray->getObjectMap()));
	
	DO_CHECK("Object Universe: Structure 1",

	delete basic;
	delete tenured;
	delete pernament;
}