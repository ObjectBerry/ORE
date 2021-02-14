#include "../Memory/MemoryAllocator.hpp"
#include "../Objects/SlotObject.hpp"


#include "SlotIterator.hpp"
#include "SlotDescription.hpp"
#include "SlotType.hpp"

#include "ObjectMap.hpp"




Object_Layout::ObjectMap::ObjectMap(unsigned short slotCount) {
	this->_sharedMap = false;
	this->_slotCount = slotCount;
	Memory::MemoryAllocator* allc = this->getAllocator();
	this->_slotDescriptions = new(this->getAllocator()) Object_Layout::SlotDescription[slotCount];
}



Object_Layout::ObjectMap* Object_Layout::ObjectMap::clone(Memory::MemoryAllocator* memoryAllocator) {
	Object_Layout::ObjectMap* clonedObjectMap = new(memoryAllocator) ObjectMap(this->_slotCount);
	for (unsigned i = 0; i < this->_slotCount; i++) {
		clonedObjectMap->_slotDescriptions[i] = this->_slotDescriptions[i];
	}
	
	return clonedObjectMap;
}

Objects::SlotObject* Object_Layout::ObjectMap::constructObject(Memory::MemoryAllocator* memoryAllocator) {
	return new(memoryAllocator) Objects::SlotObject(this);
}




// Description accessing
Object_Layout::SlotDescription* Object_Layout::ObjectMap::getDescription(unsigned short index) {
	if (index > this->getSlotCount()) {
		return nullptr;
	}
	return &(this->_slotDescriptions[index]);
}
void Object_Layout::ObjectMap::setDescription(unsigned short index, Object_Layout::SlotDescription slotDescription) {
	if (slotDescription.isParameter()) {
		return;
	}
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

