#include "../Memory/MemoryAllocator.hpp"
#include "../Object_Layout/ObjectMap.hpp"

#include "Object.hpp"

void* Objects::Object::operator new(size_t size, Memory::MemoryAllocator* memoryAllocator) {
	return memoryAllocator->allocateMemory(size);
}

Objects::Object::Object(Memory::MemoryAllocator* memoryAllocator, Object_Layout::ObjectMap* objectMap) {
	this->_objectMap = objectMap;
	this->_slotValues = static_cast<Object**>( memoryAllocator->allocateMemory(sizeof(Object*) * objectMap->getSlotCount()));
}

// factory method - use this to create bare objects
Objects::Object* Objects::Object::create(Memory::MemoryAllocator* memoryAllocator, Object_Layout::ObjectMap* objectMap) {
	return new(memoryAllocator) Objects::Object(memoryAllocator, objectMap);
}