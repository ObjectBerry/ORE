#include "../Memory/NativeAllocator.hpp"

#include "../Objects/Object.hpp"
#include "../Object_Layout/ObjectMap.hpp"
#include "../Object_Layout/SlotDescription.hpp"
#include "../Object_Layout/SlotIterator.hpp"
#include "../Object_Layout/SlotType.hpp"


#include "ObjectTesting.hpp"

Unit_Tests::ObjectTesting::ObjectTesting() : Unit_Tests::TestCase("Object Testing") { };

void Unit_Tests::ObjectTesting::runTests() {
	Memory::NativeAllocator* allocator = new Memory::NativeAllocator();

	Object_Layout::ObjectMap* objectMap = Object_Layout::ObjectMap::create(allocator, 4);

	DO_CHECK("Object Map 1", objectMap->getSlotCount() == 4);

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

	DO_CHECK("Object Map 2", clonedMap->getSlotCount() == 4);
	DO_CHECK("Object Map 3", result == true);
}