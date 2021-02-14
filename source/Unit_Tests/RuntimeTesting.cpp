#include "../Memory/BufferAllocator.hpp"

#include "../Object_Layout/ObjectMap.hpp"
#include "../Object_Layout/SlotDescription.hpp"
#include "../Object_Layout/SlotType.hpp"

#include "../Objects/SlotObject.hpp"
#include "../Objects/String.hpp"
#include "../Objects/Symbol.hpp"

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

	// Testing basic object creation
	Objects::SlotObject* empty1, * empty2;
	empty1 = objUniverse->createObject(0); 
	empty2 = objUniverse->createObject(0); 

	DO_CHECK("Object Universe: Basic SlotObject creation 1", empty1->getObjectMap() == empty2->getObjectMap());
	DO_CHECK("Object Universe: Basic SlotObject creation 2", empty1->getSlotCount() == 0); 

	Objects::Symbol* first, * second;
	first = objUniverse->createSymbol("first", Objects::SymbolType::AlphaNumerical, 0);
	second = objUniverse->createSymbol("second", Objects::SymbolType::AlphaNumerical, 0);

	Object_Layout::SlotDescription descs[2] = {
		Object_Layout::SlotDescription( first,	Object_Layout::SlotType::NormalSlot ),
		Object_Layout::SlotDescription( second,	Object_Layout::SlotType::NormalSlot )
	};
	Objects::SlotObject* values[2] = {
		(Objects::SlotObject*)(5),
		(Objects::SlotObject*)(10)
	};
	Objects::SlotObject* firstObj, * secondObj;

	firstObj = objUniverse->createObjectWithSlots(2, descs);
	secondObj = objUniverse->createObjectWithValues(2, descs, values);

	DO_CHECK("Object Universe: Basic SlotObject creation 3", secondObj->getSlotCount() == 2 && firstObj->getSlotCount() == 2); 
	DO_CHECK("Object Universe: Basic SlotObject creation 4", firstObj->getObjectMap()->getDescription(0)->getName() == first); 
	DO_CHECK("Object Universe: Basic SlotObject creation 5", secondObj->getSlot(second) == (Objects::SlotObject*)(10));


	// Testing system object creation
	Objects::ByteArray* byteArray = objUniverse->createByteArray(1); 
	Objects::String* string = objUniverse->createString("yo"); 

	DO_CHECK("Object Universe: System objects", (string->getObjectMap() == byteArray->getObjectMap()));
	
	Objects::Symbol* globalsSym, * undefSym, *parentSym;
	
	
	// Testing universe structure
	globalsSym = objUniverse->createSymbol("globals", Objects::SymbolType::AlphaNumerical, 0);
	undefSym = objUniverse->createSymbol("Undefined", Objects::SymbolType::AlphaNumerical, 0);
	parentSym = objUniverse->createSymbol("parent", Objects::SymbolType::AlphaNumerical, 0);

	DO_CHECK("Object Universe: Structure 1", objUniverse->getLobbyObject()->getSlot(globalsSym) == objUniverse->getGlobalsObject());
	DO_CHECK("Object Universe: Structure 2", objUniverse->getGlobalsObject()->getSlot(undefSym) == objUniverse->getUndefinedObject());
	DO_CHECK("Object Universe: Structure 3",
		(objUniverse->getGlobalsObject()->getSlot(undefSym))->getSlot(parentSym) == objUniverse->getTraitsObject()->getSlot(undefSym)
	);


	delete basic;
	delete tenured;
	delete pernament;
}