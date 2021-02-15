#include "../Memory/MemoryAllocator.hpp"

#include "../Object_Layout/ObjectMap.hpp"
#include "../Object_Layout/MethodMap.hpp"
#include "../Object_Layout/SlotDescription.hpp"

#include "Symbol.hpp"

#include "SlotObject.hpp"


Objects::SlotObject::SlotObject(Object_Layout::ObjectMap* objectMap) : Objects::MappedObject(objectMap) {

	this->_slotValues = objectMap->getSlotCount() == 0 ?
		nullptr :
		static_cast<SlotObject**>(this->getAllocator()->allocateMemory(sizeof(SlotObject*) * objectMap->getSlotCount()));
	this->setObjectType(Objects::ObjectType::SlotObject);
}





Objects::SlotObject* Objects::SlotObject::clone(Memory::MemoryAllocator* allocator) {
	Objects::SlotObject* clonedObject = new(allocator) Objects::SlotObject(this->getObjectMap());
	this->copyValuesInto(clonedObject);
	return clonedObject;
}

void Objects::SlotObject::copyValuesInto(Objects::SlotObject* target) {
	if (this->getObjectMap()->getSlotCount() != target->getObjectMap()->getSlotCount())
		return;
	if (this->getObjectMap()->getSlotCount() == 0)
		return;

	for (unsigned i = 0; i < this->getObjectMap()->getSlotCount(); i++) {
		target->_slotValues[i] = this->_slotValues[i];
	};
}

Objects::SlotObject* Objects::SlotObject::getSlot(Objects::Symbol* slotName) {
	int index = this->getObjectMap()->getSlotIndex(slotName);
	if (index == -1)
		return nullptr;

	return this->getValue(index);
}

bool Objects::SlotObject::setSlot(Objects::Symbol* slotName, Objects::SlotObject* reference) {
	int index = this->getObjectMap()->getSlotIndex(slotName);
	if (index == -1)
		return false;

	this->setValue(index, reference);
	return true;
}


// Proxy methods of object map



// Methods to manipulate object structure
void Objects::SlotObject::cloneSharedMap() {
	// this will be optimized in future using object map field _shared. If that field will be true , we will 
	this->_objectMap = this->getObjectMap()->clone(this->getAllocator());
}

bool Objects::SlotObject::createSlot(Object_Layout::SlotDescription newDescription, Objects::SlotObject* value) {
	signed int descIndex = this->getObjectMap()->getSlotIndex(newDescription.getName());
	if (descIndex != -1)
		return false;
	
	Object_Layout::SlotDescription* oldDescriptions = this->getObjectMap()->getSlotDescriptions();
	Objects::SlotObject** oldValues						= this->_slotValues;
	unsigned short oldSlotCount						= this->getSlotCount();

	this->_objectMap = new(this->getAllocator()) Object_Layout::ObjectMap(oldSlotCount + 1);
	this->_slotValues = static_cast<Objects::SlotObject**>(this->getAllocator()->allocateMemory(sizeof(Objects::SlotObject*) * (oldSlotCount + 1) ));
	
	for (unsigned i = 0; i < this->getSlotCount() - 1; i++) {
		this->_slotValues[i] = oldValues[i];
		this->getObjectMap()->setDescription(i, oldDescriptions[i]);
	}
	this->getObjectMap()->setDescription(oldSlotCount, newDescription);
	this->_slotValues[oldSlotCount] = value;

	return true;
};
bool Objects::SlotObject::removeSlot(Objects::Symbol* slotName) {
	signed int descIndex = this->getObjectMap()->getSlotIndex(slotName); 
	if (descIndex == -1)
		return false;

	Object_Layout::SlotDescription* oldDescriptions = this->getObjectMap()->getSlotDescriptions();
	Objects::SlotObject** oldValues = this->_slotValues;
	unsigned short oldSlotCount = this->getSlotCount();

	this->_objectMap = new(this->getAllocator()) Object_Layout::ObjectMap(oldSlotCount - 1);
	this->_slotValues = static_cast<Objects::SlotObject**>(this->getAllocator()->allocateMemory(sizeof(Objects::SlotObject*) * (oldSlotCount - 1)));

	unsigned short newIndex = 0;
	unsigned short oldIndex = 0; 
	while (newIndex < oldSlotCount - 1) {
		if (oldIndex != descIndex) {
			this->getObjectMap()->setDescription(newIndex, oldDescriptions[oldIndex]);
			this->_slotValues[newIndex] = oldValues[oldIndex];
			newIndex++;
		}
		oldIndex++;		
	}

	return true;
}