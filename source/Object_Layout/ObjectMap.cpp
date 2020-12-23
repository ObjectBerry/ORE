#include "../Memory/MemoryFacade.hpp"
#include "../Objects/Object.hpp"

#include "SlotDescription.hpp"
#include "SlotType.hpp"

#include "ObjectMap.hpp"

void* Object_Layout::ObjectMap::operator new(size_t size, Memory::MemoryFacade* memoryFacade) {
	return memoryFacade->allocate(size);
}

Object_Layout::ObjectMap::ObjectMap(Memory::MemoryFacade* memoryFacade, unsigned short slotCount) {
	this->_sharedMap = false;
	this->_slotCount = slotCount;
	this->_slotDescriptions = new(memoryFacade) Object_Layout::SlotDescription[slotCount];
}

// factory method - this is only way to create bare object map (constructor is private)
Object_Layout::ObjectMap* Object_Layout::ObjectMap::create(Memory::MemoryFacade* memoryFacade, unsigned short slotCount) {
	return new(memoryFacade) Object_Layout::ObjectMap(memoryFacade, slotCount);
}


Object_Layout::ObjectMap* Object_Layout::ObjectMap::clone(Memory::MemoryFacade* memoryFacade) {
	Object_Layout::ObjectMap* clonedObjectMap = ObjectMap::create(memoryFacade, this->_slotCount);
	for (unsigned i = 0; i < this->_slotCount; i++) {
		clonedObjectMap->_slotDescriptions[i] = this->_slotDescriptions[i];
	}
	
	return clonedObjectMap;
}

Objects::Object* Object_Layout::ObjectMap::constructObject(Memory::MemoryFacade* memoryFacade) {
	return Objects::Object::create(memoryFacade, this);
}