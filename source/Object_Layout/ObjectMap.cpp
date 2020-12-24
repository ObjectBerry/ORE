#include "../Memory/MemoryAllocator.hpp"
#include "../Objects/Object.hpp"

#include "SlotDescription.hpp"
#include "SlotType.hpp"

#include "ObjectMap.hpp"

void* Object_Layout::ObjectMap::operator new(size_t size, Memory::MemoryAllocator* memoryAllocator) {
	return memoryAllocator->allocate(size);
}

Object_Layout::ObjectMap::ObjectMap(Memory::MemoryAllocator* memoryAllocator, unsigned short slotCount) {
	this->_sharedMap = false;
	this->_slotCount = slotCount;
	this->_slotDescriptions = new(memoryAllocator) Object_Layout::SlotDescription[slotCount];
}

// factory method - this is only way to create bare object map (constructor is private)
Object_Layout::ObjectMap* Object_Layout::ObjectMap::create(Memory::MemoryAllocator* memoryAllocator, unsigned short slotCount) {
	return new(memoryAllocator) Object_Layout::ObjectMap(memoryAllocator, slotCount);
}


Object_Layout::ObjectMap* Object_Layout::ObjectMap::clone(Memory::MemoryAllocator* memoryAllocator) {
	Object_Layout::ObjectMap* clonedObjectMap = ObjectMap::create(memoryAllocator, this->_slotCount);
	for (unsigned i = 0; i < this->_slotCount; i++) {
		clonedObjectMap->_slotDescriptions[i] = this->_slotDescriptions[i];
	}
	
	return clonedObjectMap;
}

Objects::Object* Object_Layout::ObjectMap::constructObject(Memory::MemoryAllocator* memoryAllocator) {
	return Objects::Object::create(memoryAllocator, this);
}