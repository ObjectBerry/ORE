#include "../Memory/MemoryAllocator.hpp"

#include "../Object_Layout/ObjectMap.hpp"
#include "../Object_Layout/MethodMap.hpp"
#include "../Object_Layout/SlotDescription.hpp"

#include "Symbol.hpp"

#include "Object.hpp"


Objects::Object::Object(Object_Layout::ObjectMap* objectMap) {
	this->_visitedObject = false;
	this->_objectType = Objects::ObjectType::Object;

	this->_objectMap = objectMap;
	this->_slotValues = objectMap->getSlotCount() == 0 ?
		nullptr :
		static_cast<Object**>(this->getAllocator()->allocateMemory(sizeof(Object*) * objectMap->getSlotCount()));
}





Objects::Object* Objects::Object::clone(Memory::MemoryAllocator* allocator) {
	Objects::Object* clonedObject = new(allocator) Objects::Object( this->_objectMap);
	this->copyValuesInto(clonedObject);
	return clonedObject;
}

void Objects::Object::copyValuesInto(Objects::Object* target) {
	if (this->_objectMap->getSlotCount() != target->_objectMap->getSlotCount())
		return;
	if (this->_objectMap->getSlotCount() == 0)
		return;

	for (unsigned i = 0; i < this->_objectMap->getSlotCount(); i++) {
		target->_slotValues[i] = this->_slotValues[i];
	};
}

Objects::Object* Objects::Object::getSlot(Objects::Symbol* slotName) {
	int index = this->_objectMap->getSlotIndex(slotName);
	if (index == -1)
		return nullptr;

	return this->getValue(index);
}

bool Objects::Object::setSlot(Objects::Symbol* slotName, Objects::Object* reference) {
	int index = this->_objectMap->getSlotIndex(slotName);
	if (index == -1)
		return false;

	this->setValue(index, reference);
	return true;
}


// Proxy methods of object map
unsigned short Objects::Object::getSlotCount() {
	return this->_objectMap->getSlotCount();
}

bool Objects::Object::hasCode() {
	return this->_objectMap->hasCode();
}
unsigned short Objects::Object::getParameterCount() {
	if (not this->_objectMap->hasCode()) {
		return 0;
	}	
	return reinterpret_cast<Object_Layout::MethodMap*>(this->_objectMap)->getParameterCount();
}

Objects::ByteArray* Objects::Object::getBytecode() {
	if (not this->_objectMap->hasCode())
		return nullptr;

	return reinterpret_cast<Object_Layout::MethodMap*>(this->_objectMap)->getBytecode();
}

Objects::ObjectArray* Objects::Object::getLiterals() {
	if (not this->_objectMap->hasCode())
		return nullptr;

	return reinterpret_cast<Object_Layout::MethodMap*>(this->_objectMap)->getLiterals();
}


// Methods to manipulate object structure
void Objects::Object::cloneSharedMap() {
	// this will be optimized in future using object map field _shared. If that field will be true , we will 
	this->_objectMap = this->_objectMap->clone(this->getAllocator());
}

bool Objects::Object::createSlot(Object_Layout::SlotDescription newDescription, Objects::Object* value) {
	signed int descIndex = this->_objectMap->getSlotIndex(newDescription.getName());
	if (descIndex != -1)
		return false;
	
	Object_Layout::SlotDescription* oldDescriptions = this->_objectMap->getSlotDescriptions();
	Objects::Object** oldValues						= this->_slotValues;
	unsigned short oldSlotCount						= this->getSlotCount();

	this->_objectMap = new(this->getAllocator()) Object_Layout::ObjectMap(oldSlotCount + 1);
	this->_slotValues = static_cast<Objects::Object**>(this->getAllocator()->allocateMemory(sizeof(Objects::Object*) * (oldSlotCount + 1) ));
	
	for (unsigned i = 0; i < this->getSlotCount() - 1; i++) {
		this->_slotValues[i] = oldValues[i];
		this->_objectMap->setDescription(i, oldDescriptions[i]);
	}
	this->_objectMap->setDescription(oldSlotCount, newDescription);
	this->_slotValues[oldSlotCount] = value;

	return true;
};
bool Objects::Object::removeSlot(Objects::Symbol* slotName) {
	signed int descIndex = this->_objectMap->getSlotIndex(slotName); 
	if (descIndex == -1)
		return false;

	Object_Layout::SlotDescription* oldDescriptions = this->_objectMap->getSlotDescriptions();
	Objects::Object** oldValues = this->_slotValues;
	unsigned short oldSlotCount = this->getSlotCount();

	this->_objectMap = new(this->getAllocator()) Object_Layout::ObjectMap(oldSlotCount - 1);
	this->_slotValues = static_cast<Objects::Object**>(this->getAllocator()->allocateMemory(sizeof(Objects::Object*) * (oldSlotCount - 1)));

	unsigned short newIndex = 0;
	unsigned short oldIndex = 0; 
	while (newIndex < oldSlotCount - 1) {
		if (oldIndex != descIndex) {
			this->_objectMap->setDescription(newIndex, oldDescriptions[oldIndex]);
			this->_slotValues[newIndex] = oldValues[oldIndex];
			newIndex++;
		}
		oldIndex++;		
	}

	return true;
}