#include "ObjectArray.hpp"

Objects::ObjectArray::ObjectArray(basicParameter, unsigned short length) : Object(memoryAllocator, objectMap) {
	this->_length = length;
	this->_storage = static_cast<Objects::Object**>( memoryAllocator->allocateMemory(sizeof(Objects::Object*) * length));
	for (unsigned i = 0; i < this->_length; i++) {
		this->_storage[i] = 0;
	}
}


Objects::ObjectArray* Objects::ObjectArray::create(basicParameter, unsigned short length) {
	return new(memoryAllocator) Objects::ObjectArray(memoryAllocator, objectMap, length);
}

Objects::ObjectArray* Objects::ObjectArray::clone(Memory::MemoryAllocator* memoryAllocator) {
	Objects::ObjectArray* clonedArray = Objects::ObjectArray::create(memoryAllocator, this->getObjectMap(), this->_length);
	this->copyValuesInto(clonedArray);

	for (unsigned i = 0; i < this->_length; i++) {
		clonedArray->_storage[i] = this->at(i);
	}

	return clonedArray;
}