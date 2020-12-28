#include "../Memory/MemoryAllocator.hpp"
#include "../Objects/Object.hpp"

#include "SlotIterator.hpp"
#include "SlotDescription.hpp"
#include "SlotType.hpp"

#include "ObjectMap.hpp"

void* Object_Layout::ObjectMap::operator new(size_t size, Memory::MemoryAllocator* memoryAllocator) {
	return memoryAllocator->allocateMemory(size);
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



Object_Layout::SlotDescription* Object_Layout::ObjectMap::getDescription(unsigned short index) {
	if (index > this->getSlotCount()) {
		return nullptr;
	}
	return &(this->_slotDescriptions[index]);
}
void Object_Layout::ObjectMap::setDescription(unsigned short index, Object_Layout::SlotDescription slotDescription) {
	this->_slotDescriptions[index] = slotDescription;
}

Object_Layout::SlotIterator Object_Layout::ObjectMap::getIterator() {
	return Object_Layout::SlotIterator(this);
}

signed int Object_Layout::ObjectMap::getSlotIndex(Objects::Symbol* slotName) {
	for (unsigned i = 0; i < this->_slotCount; i++) {
		if (this->_slotDescriptions[i].equalName(slotName))
			return i;
	}
	return -1;
}