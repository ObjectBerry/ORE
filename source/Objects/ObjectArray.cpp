#include "ObjectArray.hpp"



Objects::ObjectArray::ObjectArray(Object_Layout::ObjectMap* objectMap, unsigned short length) : Objects::Object(objectMap) {
	this->_length = length;
	this->_storage = static_cast<Objects::Object**>(this->getAllocator()->allocateMemory(sizeof(Objects::Object*) * length));
	for (unsigned i = 0; i < this->_length; i++) {
		this->_storage[i] = 0;
	}
}




Objects::ObjectArray* Objects::ObjectArray::clone(Memory::MemoryAllocator* memoryAllocator) {
	Objects::ObjectArray* clonedArray = new(memoryAllocator)  Objects::ObjectArray( this->getObjectMap(), this->_length);
	this->copyValuesInto(clonedArray);

	for (unsigned i = 0; i < this->_length; i++) {
		clonedArray->_storage[i] = this->at(i);
	}

	return clonedArray;
}