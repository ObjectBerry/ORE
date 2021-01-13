#include "../Memory/MemoryAllocator.hpp"

#include "../Object_Layout/ObjectMap.hpp"
#include "../Object_Layout/ExecutableMap.hpp"

#include "Symbol.hpp"

#include "Object.hpp"

void* Objects::Object::operator new(size_t size, Memory::MemoryAllocator* memoryAllocator) {
	return memoryAllocator->allocateMemory(size);
}

Objects::Object::Object(basicParameter) {
	this->_visitedObject = false;
	this->_objectMap = objectMap;
	this->_slotValues = static_cast<Object**>( memoryAllocator->allocateMemory(sizeof(Object*) * objectMap->getSlotCount()));
}

// factory method - use this to create bare objects
Objects::Object* Objects::Object::create(Memory::MemoryAllocator* memoryAllocator, Object_Layout::ObjectMap* objectMap) {
	return new(memoryAllocator) Objects::Object(memoryAllocator, objectMap);
}
// this one is for creating object together with map 
Objects::Object* Objects::Object::createWithMap(Memory::MemoryAllocator* allocator, unsigned short slotCount) {
	Object_Layout::ObjectMap* newObjectMap = Object_Layout::ObjectMap::create(allocator, slotCount);

	return Objects::Object::create(allocator, newObjectMap);
}


Objects::Object* Objects::Object::clone(Memory::MemoryAllocator* allocator) {
	Objects::Object* clonedObject = Objects::Object::create(allocator, this->_objectMap);
	this->copyValuesInto(clonedObject);
	return clonedObject;
}

void Objects::Object::copyValuesInto(Objects::Object* target) {
	if (this->_objectMap->getSlotCount() != target->_objectMap->getSlotCount())
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


bool Objects::Object::hasCode() {
	return this->_objectMap->hasCode();
}
unsigned short Objects::Object::getParameterCount() {
	if (not this->_objectMap->hasCode()) {
		return 0;
	}	
	return reinterpret_cast<Object_Layout::ExecutableMap*>(this->_objectMap)->getParameterCount();
}