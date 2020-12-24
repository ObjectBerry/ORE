#include "../Memory/NativeAllocator.hpp"
#include "../Objects/Object.hpp"
#include "../Object_Layout/ObjectMap.hpp"


#include "ObjectTesting.hpp"

Unit_Tests::ObjectTesting::ObjectTesting() : Unit_Tests::TestCase("Object Testing") { };

void Unit_Tests::ObjectTesting::runTests() {
	Memory::NativeAllocator* allocator = new Memory::NativeAllocator();

	Object_Layout::ObjectMap* objectMap = Object_Layout::ObjectMap::create(allocator, 4);

	DO_CHECK("Object Map 1", objectMap->getSlotCount() == 4);


}