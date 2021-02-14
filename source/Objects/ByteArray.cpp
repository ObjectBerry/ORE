#include "../Object_Layout/ObjectMap.hpp"

#include "ByteArray.hpp"



Objects::ByteArray::ByteArray(Object_Layout::ObjectMap* objectMap, unsigned short length) : Objects::SlotObject(objectMap) {
	this->_length = length;
	this->_storage = this->getAllocator()->allocateBytes(length);
	for (unsigned i = 0; i < this->_length; i++) {
		this->_storage[i] = 0;
	}

	this->_objectType = Objects::ObjectType::ByteArray;
}
Objects::ByteArray::ByteArray(Object_Layout::ObjectMap* objectMap, const char* characters) : Objects::SlotObject(objectMap) {
	this->_length = 0;
	while (characters[_length] != '\0')
		this->_length++;
	this->_length++;

	this->_storage = const_cast<char*>(characters);

	this->_objectType = Objects::ObjectType::ByteArray;
}


Objects::ByteArray* Objects::ByteArray::clone(Memory::MemoryAllocator* memoryAllocator) {
	Objects::ByteArray* clonedArray = new (memoryAllocator) Objects::ByteArray( this->getObjectMap(), this->_length);
	this->copyValuesInto(clonedArray);

	for (unsigned i = 0; i < this->_length; i++) {
		clonedArray->_storage[i] = this->at(i);
	}

	return clonedArray;
}
Objects::ByteArray* Objects::ByteArray::cloneResize(Memory::MemoryAllocator* memoryAllocator, unsigned short newLength) {
	Objects::ByteArray* clonedArray = new (memoryAllocator) Objects::ByteArray(this->getObjectMap(), newLength);
	this->copyValuesInto(clonedArray);

	unsigned short usedLength = this->_length > newLength ?
		newLength : 
		this->_length;

	for (unsigned i = 0; i < usedLength; i++) {
		clonedArray->atPut(i, this->at(i));
	}

	return clonedArray;
}