#include "../Memory/BufferAllocator.hpp"

#include "../Sending/LookupResult.hpp"
#include "../Sending/SendMachine.hpp"
#include "../Sending/ObjectQueue.hpp"
#include "../Objects/Symbol.hpp"
#include "../Objects/SymbolType.hpp"
#include "../Object_Layout/ObjectMap.hpp"
#include "../Object_Layout/SlotDescription.hpp"
#include "../Object_Layout/SlotType.hpp"

#include "SendingTesting.hpp"

Unit_Tests::SendingTesting::SendingTesting() : Unit_Tests::TestCase("Sending Tests") {};

void Unit_Tests::SendingTesting::runTests() {
	this->testingQueue();
	this->testingSendMachine();
}

void Unit_Tests::SendingTesting::testingQueue() {
	Memory::BufferAllocator* allocator = new Memory::BufferAllocator(400);
	Sending::ObjectQueue objectQueue(4);

	Objects::Object* first, * second, * third;
	first = Objects::Object::createWithMap(allocator, 1);
	second = first->clone(allocator);
	third = second->clone(allocator);

	DO_CHECK("Object queue: check of emptyness 1", objectQueue.isEmpty());
	objectQueue.enqueue(first);
	DO_CHECK("Object queue: check of emptyness 2", objectQueue.isEmpty() == false);

	objectQueue.enqueue(second);
	objectQueue.enqueue(third);

	DO_CHECK("Object queue: dequeue 1", objectQueue.dequeue() == first);
	DO_CHECK("Object queue: dequeue 2", objectQueue.dequeue() == second);
	DO_CHECK("Object queue: dequeue 3", objectQueue.dequeue() == third);
	// Testing queue circularity 

	objectQueue.enqueue(first);
	objectQueue.enqueue(second);
	objectQueue.dequeue();

	DO_CHECK("Object queue: circularity test", objectQueue.dequeue() == second);

	delete allocator;
}

// helper functions
Object_Layout::ObjectMap* symbolMap;
Memory::BufferAllocator* symbolAllocator;
Objects::Symbol* createSym(const char* name) {
	return Objects::Symbol::create(symbolAllocator, symbolMap, (char*)name, Objects::SymbolType::AlphaNumerical, 0);
}

void setValue(Objects::Object* obj, Objects::Object* value, Object_Layout::SlotDescription slotDescription) {
	Object_Layout::ObjectMap* objMap = obj->getObjectMap();
	for (unsigned i = 0; i < objMap->getSlotCount(); i++) {
		if (not objMap->getDescription(i)->isValid()) {
			objMap->setDescription(i, slotDescription);
			obj->setValue(i, value);
			return;
		}
	}
};
// helper functions

void Unit_Tests::SendingTesting::testingSendMachine() {
	Memory::BufferAllocator* allocator = new Memory::BufferAllocator(1000);
	Sending::SendMachine* sendMachine = new Sending::SendMachine(20, 20, 20);

	Objects::Object* reciever = Objects::Object::createWithMap(allocator, 3);
	Objects::Object* firstParent = Objects::Object::createWithMap(allocator, 4);
	Objects::Object* secondParent = Objects::Object::createWithMap(allocator, 3);
	Objects::Object* sharedParent = Objects::Object::createWithMap(allocator, 2);


	Objects::Object* target1 = Objects::Object::createWithMap(allocator, 1);
	Objects::Object* target2 = target1->clone(allocator);
	Objects::Object* target3 = target1->clone(allocator);
	Objects::Object* target4 = target1->clone(allocator);
	Objects::Object* target5 = target1->clone(allocator);
	Objects::Object* duplicate = target1->clone(allocator);

	symbolMap = Object_Layout::ObjectMap::create(allocator, 1);
	symbolAllocator = allocator;


	Objects::Symbol* parentSymbol =		createSym("parent");   //Universe::getUniverse()->forSymbol("parent", Utility::SymbolType::AlphaNumerical, 0);
	Objects::Symbol* duplicateSymbol =	createSym("duplicate");
	Objects::Symbol* missing =			createSym("missing"); 
	Objects::Symbol* target1Symbol =	createSym("target1");
	Objects::Symbol* target2Symbol =	createSym("target2");
	Objects::Symbol* target3Symbol =	createSym("target3");
	Objects::Symbol* target4Symbol =	createSym("target4");
	
	Object_Layout::SlotDescription parenDescription(parentSymbol, Object_Layout::SlotType::ParentSlot);

	Sending::LookupResult lookupResult;
	
	// Setting object graph
	setValue(reciever, firstParent,			Object_Layout::SlotDescription(createSym("parent1"), Object_Layout::SlotType::ParentSlot) );
	setValue(reciever, secondParent,		Object_Layout::SlotDescription(createSym("parent2"), Object_Layout::SlotType::ParentSlot));
	setValue(firstParent, sharedParent,		parenDescription);
	setValue(secondParent, sharedParent,	parenDescription);

	// setting targets
	setValue(reciever,		target1,	Object_Layout::SlotDescription(target1Symbol,	Object_Layout::SlotType::NormalSlot));
	setValue(firstParent,	target2,	Object_Layout::SlotDescription(target2Symbol,	Object_Layout::SlotType::NormalSlot));
	setValue(sharedParent,	target3,	Object_Layout::SlotDescription(target3Symbol,	Object_Layout::SlotType::NormalSlot));
	setValue(firstParent,	duplicate,	Object_Layout::SlotDescription(duplicateSymbol, Object_Layout::SlotType::NormalSlot));
	setValue(secondParent,  duplicate,	Object_Layout::SlotDescription(duplicateSymbol, Object_Layout::SlotType::NormalSlot));
	setValue(firstParent,	target4,	Object_Layout::SlotDescription(target4Symbol,	Object_Layout::SlotType::NormalSlot));
	setValue(sharedParent,	target1,	Object_Layout::SlotDescription(target4Symbol,	Object_Layout::SlotType::NormalSlot));

	//testing
	lookupResult = sendMachine->sendMessage(reciever, target1Symbol, false);
	DO_CHECK("Normal send - target is in reciever", lookupResult._resultObject == target1 && lookupResult._resultState == Sending::LookupState::OK);
	
	lookupResult = sendMachine->sendMessage(reciever, target2Symbol, false);
	DO_CHECK("Normal send - target is in parent", lookupResult._resultObject == target2 && lookupResult._resultState == Sending::LookupState::OK);
	
	lookupResult = sendMachine->sendMessage(reciever, target3Symbol, false);
	DO_CHECK("Normal send - target is in 2nd generation", lookupResult._resultObject == target3 && lookupResult._resultState == Sending::LookupState::OK);

	lookupResult = sendMachine->sendMessage(reciever, missing, false);
	DO_CHECK("Normal send - slot doesnt exist", lookupResult._resultObject == nullptr && lookupResult._resultState == Sending::LookupState::ZeroResults);

	lookupResult = sendMachine->sendMessage(reciever, duplicateSymbol, false);
	DO_CHECK("Normal send - duplicate in same generation", lookupResult._resultObject == nullptr && lookupResult._resultState == Sending::LookupState::MultipleResults);
	
	lookupResult = sendMachine->sendMessage(reciever, target4Symbol, false);
	DO_CHECK("Normal send - duplicate  in different generations", lookupResult._resultObject == target4 && lookupResult._resultState == Sending::LookupState::OK);
	
	lookupResult = sendMachine->sendMessage(firstParent, target4Symbol, true);
	DO_CHECK("Resend - indirect delegation", lookupResult._resultObject == target1 && lookupResult._resultState == Sending::LookupState::OK);

	delete sendMachine;
	delete allocator;
}