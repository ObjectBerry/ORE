#include "../Memory/MemoryAllocator.hpp"
#include "../Objects/Object.hpp"

#include "SlotType.hpp"

#include "SlotDescription.hpp"

void* Object_Layout::SlotDescription::operator new[](size_t size, Memory::MemoryAllocator* memoryAllocator) {
	return memoryAllocator->allocateMemory(size);
}
Object_Layout::SlotDescription::SlotDescription() {
	//this->_slotName = nullptr;
	this->_slotType = Object_Layout::SlotType::UnititalizedSlot;

}

void Object_Layout::SlotDescription::setAll(Object_Layout::SlotType slotType) {
	
	this->_slotType = slotType;
}
