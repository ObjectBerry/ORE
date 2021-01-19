#include "../Memory/BufferAllocator.hpp"

#include "../Objects/ObjectType.hpp"
#include "../Objects/SmallInt.hpp"
#include "../Objects/Symbol.hpp"
#include "../Objects/ObjectFactory.hpp"

#include "../Compiler/ByteTranslator.hpp"

#include "CompilerTesting.hpp"

Unit_Tests::CompilerTesting::CompilerTesting() : Unit_Tests::TestCase("Compiler testing") {};


void Unit_Tests::CompilerTesting::runTests() {
	this->testingByteTranslator();
}

void Unit_Tests::CompilerTesting::testingByteTranslator() {
	Memory::MemoryAllocator* allocator = new Memory::BufferAllocator(1000);
	Objects::ObjectFactory* objectFactory = new Objects::ObjectFactory(allocator, allocator);

	Objects::Object* result;
	//SmallInt translation 
	char smallIntBytes[] = { 0x00, 0x00, 0x00, 0x05 };
	
	result = Compiler::ByteTranslator(objectFactory, smallIntBytes, 4).translateSmallInt();

	DO_CHECK("Byte translator: SmallInt translation 1", result->getType() == Objects::ObjectType::SmallInt);
	DO_CHECK("Byte translator: SmallInt translation 2", reinterpret_cast<Objects::SmallInt*>(result)->getValue() == 5);

	// Symbol translation
	char symbolBytes[] = { 0xAA, 0x00, 0x01, 'A', 'B', 'C', 0x00 };
	result = Compiler::ByteTranslator(objectFactory, symbolBytes, 7).translateSymbol();

	DO_CHECK("Byte translator: Symbol translation 1", result->getType() == Objects::ObjectType::Symbol); 
	DO_CHECK("Byte translator: Symbol translation 1", reinterpret_cast<Objects::Symbol*>( result)->equalValue("ABC", Objects::SymbolType::AlphaNumerical, 1));

	delete objectFactory;
	delete allocator;
}