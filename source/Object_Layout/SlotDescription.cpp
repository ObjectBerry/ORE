#include "../Memory/MemoryAllocator.hpp"
#include "../Objects/SlotObject.hpp"
#include "../Objects/Symbol.hpp"

#include "SlotType.hpp"

#include "SlotDescription.hpp"

void* Object_Layout::SlotDescription::operator new[](size_t size, Memory::MemoryAllocator* memoryAllocator) {
	return memoryAllocator->allocateMemory(size);
}
Object_Layout::SlotDescription::SlotDescription() {
	this->_slotName = nullptr;
	this->_slotType = Object_Layout::SlotType::UnititalizedSlot;

}
Object_Layout::SlotDescription::SlotDescription(Objects::Symbol* slotName, Object_Layout::SlotType slotType) {
	this->_slotName = slotName;
	this->_slotType = slotType;
}

void Object_Layout::SlotDescription::setAll(Objects::Symbol* slotName ,Object_Layout::SlotType slotType) {
	this->_slotName = slotName;
	this->_slotType = slotType;
}

bool Object_Layout::SlotDescription::equalSlot(Object_Layout::SlotDescription* other) {
	if (!this->_slotName->equalObject(other->_slotName)) {
		return false;
	}
	if(this->_slotType != other->_slotType){
		return false;
	}
	return true;
}
bool Object_Layout::SlotDescription::equalName(Objects::Symbol* otherSymbol) {
	if (this->_slotName == nullptr) {
		return false;
	}
	return (this->_slotName->equalObject(otherSymbol));
}
bool Object_Layout::SlotDescription::isParameter() {
	return (
		(this->_slotType == Object_Layout::SlotType::NormalParameter)
		||
		(this->_slotType == Object_Layout::SlotType::ParentParameter)
	);
}

bool Object_Layout::SlotDescription::isParent() {
	return (
		(this->_slotType == Object_Layout::SlotType::ParentSlot)
		||
		(this->_slotType == Object_Layout::SlotType::ParentParameter)
	);
}
bool Object_Layout::SlotDescription::isValid() {
	return this->_slotType != Object_Layout::SlotType::UnititalizedSlot;
}