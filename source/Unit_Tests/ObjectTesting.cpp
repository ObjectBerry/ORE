#include "../Memory/NativeAllocator.hpp"

#include "../Objects/Object.hpp"
#include "../Objects/ByteArray.hpp"

#include "../Object_Layout/ObjectMap.hpp"
#include "../Object_Layout/SlotDescription.hpp"
#include "../Object_Layout/SlotIterator.hpp"
#include "../Object_Layout/SlotType.hpp"


#include "ObjectTesting.hpp"

Unit_Tests::ObjectTesting::ObjectTesting() : Unit_Tests::TestCase("Object Testing") { };

void Unit_Tests::ObjectTesting::runTests() {
	Memory::NativeAllocator* allocator = new Memory::NativeAllocator();

	Object_Layout::ObjectMap* objectMap = Object_Layout::ObjectMap::create(allocator, 4);

	DO_CHECK("Object Map creation", objectMap->getSlotCount() == 4);

	Object_Layout::SlotDescription descriptor;
	descriptor.setAll(Object_Layout::SlotType::NormalParameter);
	objectMap->setDescription(1, descriptor);
	Object_Layout::ObjectMap* clonedMap = objectMap->clone(allocator);
	
	
	
	Object_Layout::SlotIterator first = objectMap->getIterator();
	Object_Layout::SlotIterator second = clonedMap->getIterator();
	bool result = true;
	for (unsigned i = 0; i < clonedMap->getSlotCount(); i++) {
		Object_Layout::SlotDescription* a, *b;
		a = first.nextItem();
		b = second.nextItem();
		if (not (a->equalObject(b))) {
			result = false;
			break;
		}
	}

	DO_CHECK("Object Map clonning 1", clonedMap->getSlotCount() == 4);
	DO_CHECK("Object Map clonning 2", result == true);


	// Object testing

	Objects::Object* object = objectMap->constructObject(allocator);
	object->setValue(1, (Objects::Object*)0x0000000A);

	Objects::Object* clonedObject = object->clone(allocator);

	DO_CHECK("Object clonning", object->getValue(1) == clonedObject->getValue(1));


	// Byte array testing
	// yes , we will use same object map in every type of object. This wouldnt happend in 
	Objects::ByteArray* byteArray1 = Objects::ByteArray::create(allocator, objectMap, 2);

	byteArray1->atPut(0, 10);
	byteArray1->atPut(1, 35);

	Objects::ByteArray* byteArray2 = byteArray1->clone(allocator);
	DO_CHECK("ByteArray clonning", (byteArray2->at(0) == 10) && (byteArray2->at(1) == 35));
}