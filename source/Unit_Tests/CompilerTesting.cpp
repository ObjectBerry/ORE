#include "../Memory/BufferAllocator.hpp"

#include "../Object_Layout/ObjectMap.hpp"
#include "../Object_Layout/SlotDescription.hpp"

#include "../Objects/ObjectType.hpp"
#include "../Objects/SmallInt.hpp"
#include "../Objects/Symbol.hpp"
#include "../Objects/ObjectFactory.hpp"

#include "../Compiler/LiteralType.hpp"
#include "../Compiler/TranslatorError.hpp"
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
	DO_CHECK("Byte translator: Symbol translation 2", reinterpret_cast<Objects::Symbol*>( result)->equalValue("ABC", Objects::SymbolType::AlphaNumerical, 1));


	// Object translation
	char obj1Bytes[] = { 
		0x00, 0x02,
			0xAA, 0x00, 0x00, 'A', 0x00, 0xAA, 0x10, 0x00, 0x00, 0x00, 0x05,
			0xAA, 0x00, 0x00, 'p',  'a',  'r',  'e',  'n',  't', 0x00, 0xAF, 0x10, 0x00, 0x00, 0x00 ,0x0A
		
	};
	result = Compiler::ByteTranslator(objectFactory, obj1Bytes, sizeof(obj1Bytes)).translateObject();
	DO_CHECK("Byte translator: Object translation 1", result->getObjectMap()->getSlotCount() == 2);
	DO_CHECK("Byte translator: Object translation 2", result->getValue(0)->getType() == Objects::ObjectType::SmallInt);
	DO_CHECK("Byte translator: Object translation 3", 
		reinterpret_cast<Objects::SmallInt*>( 
			result->getSlot(objectFactory->createSymbol("A", Objects::SymbolType::AlphaNumerical, 0))
		)->getValue() == 5
	);
	DO_CHECK("Byte translator: Object translation 4", result->getObjectMap()->getDescription(1)->isParent());
	

	// Method translation
	char methodBytes[] = {
		0x00, 0x01,
			0xAA, 0x00, 0x00, 'A', 0x00, 0xFA, 0x00,
			0x01, 0x02,
			0x00, 0x01, 0x00, 0x02,
			0x10, 0x00, 0x00, 0x00, 0x0A,
			0x20, 0x01,
	};

	result = Compiler::ByteTranslator(objectFactory, methodBytes, sizeof(methodBytes)).translateMethod();
	DO_CHECK("Byte Translator: Method translation 1", result->getParameterCount() == 2);

	delete objectFactory;
	delete allocator;
}