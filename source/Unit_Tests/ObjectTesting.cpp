#include "../Memory/NativeAllocator.hpp"

#include "../Objects/Object.hpp"
#include "../Objects/ByteArray.hpp"
#include "../Objects/Symbol.hpp"

#include "../Object_Layout/ObjectMap.hpp"
#include "../Object_Layout/SlotDescription.hpp"
#include "../Object_Layout/SlotIterator.hpp"
#include "../Object_Layout/SlotType.hpp"


#include "ObjectTesting.hpp"

Unit_Tests::ObjectTesting::ObjectTesting() : Unit_Tests::TestCase("Object Testing") { };

void Unit_Tests::ObjectTesting::runTests() {
	// Native allocator used by all objects - just facade for malloc
	Memory::NativeAllocator* allocator = new Memory::NativeAllocator();


	// Object map creation ******************
	Object_Layout::ObjectMap* objectMap = Object_Layout::ObjectMap::create(allocator, 2);
	
	DO_CHECK("Object Map creation", objectMap->getSlotCount() == 2);

	//Object map slot indexing *************
	Objects::Symbol* testSymbol1 = Objects::Symbol::create(allocator, objectMap, (char*)"test", Objects::SymbolType::AlphaNumerical, 0);
	Objects::Symbol* testSymbol2 = Objects::Symbol::create(allocator, objectMap, (char*)"test2", Objects::SymbolType::AlphaNumerical, 0);
	objectMap->setDescription(1, Object_Layout::SlotDescription(testSymbol1, Object_Layout::SlotType::NormalSlot));
	
	DO_CHECK("Object map slot indexing 1", objectMap->getSlotIndex(testSymbol1) == 1);
	DO_CHECK("Object map slot indexing 2", objectMap->getSlotIndex(testSymbol2) == -1);
	
	// Object map clonning***
	Object_Layout::ObjectMap* clonedMap = objectMap->clone(allocator);
	
	Object_Layout::SlotIterator first = objectMap->getIterator();
	Object_Layout::SlotIterator second = clonedMap->getIterator();
	bool result = true;
	for (unsigned i = 0; i < clonedMap->getSlotCount(); i++) {
		Object_Layout::SlotDescription* a, *b;
		a = first.nextItem();
		b = second.nextItem();
		if (not (a->equalSlot(b))) {
			result = false;
			break;
		}
	}

	DO_CHECK("Object Map clonning 1", clonedMap->getSlotCount() == 2);
	DO_CHECK("Object Map clonning 2", result == true);
	DO_CHECK("Object Map clonning 3", objectMap->getSlotIndex(testSymbol1) == 1);

	// Object slot accessing
	Objects::Object* testObject1 = objectMap->constructObject(allocator);
	bool setResult = testObject1->setSlot(testSymbol1, (Objects::Object*)10); 

	DO_CHECK("Object slot accessing 1", setResult);
	DO_CHECK("Object slot accessing 2", testObject1->getSlot(testSymbol1) == (Objects::Object*)10);
	DO_CHECK("Object slot accessing 3", testObject1->getSlot(testSymbol2) == nullptr);
	DO_CHECK("Object slot accessing 4", testObject1->setSlot(testSymbol2, nullptr) == false);
	
	// Object clonning
	Objects::Object* testObject2 = testObject1->clone(allocator);
	
	DO_CHECK("Object clonning 1", testObject1->getSlot(testSymbol1) == (Objects::Object*)10); 

	// Byte array testing
	// yes , we will use same object map in every type of object. This wouldnt happend in real situtation.
	Objects::ByteArray* testByteArray1 = Objects::ByteArray::create(allocator, objectMap, 2);

	testByteArray1->atPut(0, 10);
	testByteArray1->atPut(1, 35);

	Objects::ByteArray* testByteArray2 = testByteArray1->clone(allocator);
	DO_CHECK("ByteArray clonning", (testByteArray2->at(0) == 10) && (testByteArray2->at(1) == 35));

	// Symbol testing
	
	// we alredy have two symbols from before - we only need one another for comparision
	Objects::Symbol* testSymbol3 = Objects::Symbol::create(allocator, objectMap, (char*)"test", Objects::SymbolType::AlphaNumerical, 0);
	DO_CHECK("Symbol comparing 1", (testSymbol1->equalObject(testSymbol2)) == false);
	DO_CHECK("Symbol comparing 2", testSymbol1->equalObject(testSymbol3));
}