#include "../Memory/BufferAllocator.hpp"

#include "../Objects/Object.hpp"
#include "../Objects/ByteArray.hpp"
#include "../Objects/Symbol.hpp"
#include "../Objects/ObjectArray.hpp"
#include "../Objects/Process.hpp"
#include "../Objects/Context.hpp"
#include "../Objects/Code.hpp"



#include "../Object_Layout/MethodMap.hpp"
#include "../Object_Layout/ObjectMap.hpp"
#include "../Object_Layout/SlotDescription.hpp"
#include "../Object_Layout/SlotIterator.hpp"
#include "../Object_Layout/SlotType.hpp"


#include "ObjectTesting.hpp"

Unit_Tests::ObjectTesting::ObjectTesting() : Unit_Tests::TestCase("Object Testing") { };
void Unit_Tests::ObjectTesting::runTests() {
	this->testingObjectMap();
	this->testingObjects();
}

// Testing of object maps
//
void Unit_Tests::ObjectTesting::testingObjectMap() {
	Memory::BufferAllocator* allocator = new Memory::BufferAllocator(1000);
	
	Object_Layout::ObjectMap* objectMap = Object_Layout::ObjectMap::create(allocator, 2);

	DO_CHECK("ObjectMap: creation", objectMap->getSlotCount() == 2);

	//Object map slot indexing *************
	Objects::Symbol* testSymbol1 = Objects::Symbol::create(allocator, objectMap, (char*)"test", Objects::SymbolType::AlphaNumerical, 0);
	Objects::Symbol* testSymbol2 = Objects::Symbol::create(allocator, objectMap, (char*)"test2", Objects::SymbolType::AlphaNumerical, 0);
	objectMap->setDescription(0, Object_Layout::SlotDescription(testSymbol1, Object_Layout::SlotType::NormalSlot));

	DO_CHECK("ObjectMap: slot indexing 1", objectMap->getSlotIndex(testSymbol1) == 0);
	DO_CHECK("ObjectMap: slot indexing 2", objectMap->getSlotIndex(testSymbol2) == -1);

	//ObjectMap parameter detection
	objectMap->setDescription(0, Object_Layout::SlotDescription(testSymbol2, Object_Layout::SlotType::NormalParameter));
	DO_CHECK("ObjectMap: parameter detection", objectMap->getSlotIndex(testSymbol2) == -1);


	// Object map clonning***
	Object_Layout::ObjectMap* clonedMap = objectMap->clone(allocator);

	Object_Layout::SlotIterator first = objectMap->getIterator();
	Object_Layout::SlotIterator second = clonedMap->getIterator();
	bool result = true;
	for (unsigned i = 0; i < clonedMap->getSlotCount(); i++) {
		Object_Layout::SlotDescription* a, * b;
		a = first.nextItem();
		b = second.nextItem();
		if (not (a->equalSlot(b))) {
			result = false;
			break;
		}
	}

	DO_CHECK("ObjectMap: clonning 1", clonedMap->getSlotCount() == 2);
	DO_CHECK("ObjectMap: clonning 2", result == true);
	DO_CHECK("ObjectMap: clonning 3", objectMap->getSlotIndex(testSymbol1) == 0);

	// Execution map
	Objects::ByteArray* bytecodes = Objects::ByteArray::create(allocator, objectMap, 3);
	Objects::ObjectArray* literals = Objects::ObjectArray::create(allocator, objectMap, 1);
	bytecodes->atPut(0, 5);
	bytecodes->atPut(1, 10);
	bytecodes->atPut(2, 15);

	

	Object_Layout::MethodMap* executableMap = Object_Layout::MethodMap::create(allocator, 1, bytecodes, literals,  Object_Layout::ScopeType::Dynamic, Object_Layout::ReturnType::Implicit);
	executableMap->setDescription(0, Object_Layout::SlotDescription(testSymbol1, Object_Layout::SlotType::NormalParameter));
	
	DO_CHECK("Executable Map: parameters adding", executableMap->getParameterCount() == 1);
	
	// Execution map clonning
	Object_Layout::MethodMap* secondExecutableMap = executableMap->clone(allocator);
	DO_CHECK("Executable Map: clonning 1", secondExecutableMap->getParameterCount() == executableMap->getParameterCount());
	DO_CHECK("Executable Map: clonning 2", secondExecutableMap->getBytecode()		!= executableMap->getBytecode());
	DO_CHECK("Executable Map: clonning 2", secondExecutableMap->getLiterals()		!= executableMap->getLiterals());
	DO_CHECK("Executable Map: clonning 4", secondExecutableMap->getScopeType()		== executableMap->getScopeType());
	DO_CHECK("Executable Map: clonning 5", secondExecutableMap->getReturnType()		== executableMap->getReturnType());
	delete allocator;
}

// Testing of system objects
//
void Unit_Tests::ObjectTesting::testingObjects() {
	Memory::BufferAllocator* allocator = new Memory::BufferAllocator(2500);


	Object_Layout::ObjectMap* objectMap = Object_Layout::ObjectMap::create(allocator, 2);


	Objects::Symbol* testSymbol1 = Objects::Symbol::create(allocator, objectMap, (char*)"test1", Objects::SymbolType::AlphaNumerical, 0);
	Objects::Symbol* testSymbol2 = Objects::Symbol::create(allocator, objectMap, (char*)"test2", Objects::SymbolType::AlphaNumerical, 0);
	objectMap->setDescription(1, Object_Layout::SlotDescription(testSymbol1, Object_Layout::SlotType::NormalSlot));

	// Object slot accessing
	Objects::Object* testObject1 = objectMap->constructObject(allocator);
	bool setResult = testObject1->setSlot(testSymbol1, (Objects::Object*)10); 

	DO_CHECK("Object: slot accessing 1", setResult);
	DO_CHECK("Object: slot accessing 2", testObject1->getSlot(testSymbol1) == (Objects::Object*)10);
	DO_CHECK("Object: slot accessing 3", testObject1->getSlot(testSymbol2) == nullptr);
	DO_CHECK("Object: slot accessing 4", testObject1->setSlot(testSymbol2, nullptr) == false);
	
	// Object clonning
	Objects::Object* testObject2 = testObject1->clone(allocator);
	
	DO_CHECK("Object: clonning 1", testObject1->getSlot(testSymbol1) == (Objects::Object*)10); 

	// Byte array testing
	// yes , we will use same object map in every type of object. This wouldnt happend in real situtation.
	Objects::ByteArray* testByteArray1 = Objects::ByteArray::create(allocator, objectMap, 2);

	testByteArray1->atPut(0, 10);
	testByteArray1->atPut(1, 35);

	Objects::ByteArray* testByteArray2 = testByteArray1->clone(allocator);
	DO_CHECK("ByteArray: clonning", (testByteArray2->at(0) == 10) && (testByteArray2->at(1) == 35));

	// Symbol testing
	
	// we alredy have two symbols from before - we only need one another for comparision
	Objects::Symbol* testSymbol3 = Objects::Symbol::create(allocator, objectMap, (char*)"test1", Objects::SymbolType::AlphaNumerical, 0);
	DO_CHECK("Symbol: comparing 1", (testSymbol1->equalObject(testSymbol2)) == false);
	DO_CHECK("Symbol: comparing 2", testSymbol1->equalObject(testSymbol3));
	
	// Object array testing 

	Objects::ObjectArray* testObjectArray1, * testObjectArray2;
	testObjectArray1 = Objects::ObjectArray::create(allocator, objectMap, 1);
	testObjectArray1->atPut(0, testObject1); // we will use test object from object access testing 
	testObjectArray2 = testObjectArray1->clone(allocator);

	DO_CHECK("ObjectArray: clonning", testObjectArray2->at(0) == testObject1);


	// Context testing
	//First we will create method - object with code
	Objects::ByteArray* bytecodes = Objects::ByteArray::create(allocator, objectMap, 3); 
	bytecodes->atPut(0, 5);
	bytecodes->atPut(1, 10);
	bytecodes->atPut(2, 15);
	
	Objects::ObjectArray* literals = Objects::ObjectArray::create(allocator, objectMap, 1);
	literals->atPut(0, testObject1);

	
	Object_Layout::MethodMap* methodMap = Object_Layout::MethodMap::create(allocator, 2, bytecodes, literals, Object_Layout::ScopeType::Lexical, Object_Layout::ReturnType::Implicit );
	
	Objects::Context* testContext1 = Objects::Context::create(
		allocator,
		objectMap,
		nullptr,
		methodMap->constructObject(allocator)
	);
	
	
	DO_CHECK("Context: literal access", testContext1->getLiteral(0) == testObject1);
	DO_CHECK("Context: instructions access 1", testContext1->getBytecode() == 5);
	testContext1->incIndex();
	DO_CHECK("Context: instructions access 2", testContext1->getBytecode() == 10);
	testContext1->setIndex(3);
	DO_CHECK("Context: finish testing", testContext1->finished());

	testContext1->setIndex(0);
	Objects::Context* testContext2 = testContext1->clone(allocator);
	
	DO_CHECK("Context: clonning 1", testContext2->getBytecode() == testContext1->getBytecode());
	DO_CHECK("Context: clonning 2", testContext2->getLiteral(0) == testObject1);
 	
	//Process testing




	delete allocator;
}
