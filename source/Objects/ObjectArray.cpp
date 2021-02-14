#include "ObjectArray.hpp"



Objects::ObjectArray::ObjectArray(Object_Layout::ObjectMap* objectMap, unsigned short length) : Objects::SlotObject(objectMap) {
	this->_length = length;
	this->_storage = static_cast<Objects::SlotObject**>(this->getAllocator()->allocateMemory(sizeof(Objects::SlotObject*) * length));
	for (unsigned i = 0; i < this->_length; i++) {
		this->_storage[i] = 0;
	}

	this->_objectType = Objects::ObjectType::ObjectArray;
}


Objects::ObjectArray* Objects::ObjectArray::clone(Memory::MemoryAllocator* memoryAllocator) {
	Objects::ObjectArray* clonedArray = new(memoryAllocator)  Objects::ObjectArray( this->getObjectMap(), this->_length);
	this->copyValuesInto(clonedArray);

	for (unsigned i = 0; i < this->_length; i++) {
		clonedArray->_storage[i] = this->at(i);
	}

	return clonedArray;
}

Objects::ObjectArray* Objects::ObjectArray::cloneResize(Memory::MemoryAllocator* memoryAllocator, unsigned short newLength) {
	Objects::ObjectArray* clonedArray = new (memoryAllocator) Objects::ObjectArray(this->getObjectMap(), newLength);
	this->copyValuesInto(clonedArray);

	unsigned short usedLength = this->_length > newLength ?
		newLength :
		this->_length;

	for (unsigned i = 0; i < usedLength; i++) {
		clonedArray->atPut(i, this->at(i));
	}

	return clonedArray;
}