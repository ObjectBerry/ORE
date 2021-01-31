#include "../Object_Layout/ObjectMap.hpp"

#include "ByteArray.hpp"

Objects::ByteArray::ByteArray(basicParameter, unsigned short length) : Object(memoryAllocator, objectMap){
	this->_length = length;
	this->_storage = memoryAllocator->allocateBytes(length);
	for (unsigned i = 0; i < this->_length; i++) {
		this->_storage[i] = 0;
	}
}
Objects::ByteArray::ByteArray(basicParameter, char* characters) : Object(memoryAllocator, objectMap) {
	this->_length = 0;
	while (characters[_length] != '\0')
		this->_length++;
	this->_length++;

	this->_storage = characters;
}

Objects::ByteArray::ByteArray(Object_Layout::ObjectMap* objectMap, unsigned short length) : Objects::Object(objectMap) {
	this->_length = length;
	this->_storage = this->getAllocator()->allocateBytes(length);
	for (unsigned i = 0; i < this->_length; i++) {
		this->_storage[i] = 0;
	}
}
Objects::ByteArray::ByteArray(Object_Layout::ObjectMap* objectMap, const char* characters) : Objects::Object(objectMap) {
	this->_length = 0;
	while (characters[_length] != '\0')
		this->_length++;
	this->_length++;

	this->_storage = const_cast<char*>(characters);
}

Objects::ByteArray* Objects::ByteArray::create(basicParameter, unsigned short length) {
	return new(memoryAllocator) Objects::ByteArray(memoryAllocator, objectMap, length);
}

Objects::ByteArray* Objects::ByteArray::clone(Memory::MemoryAllocator* memoryAllocator) {
	Objects::ByteArray* clonedArray = Objects::ByteArray::create(memoryAllocator, this->getObjectMap(), this->_length);
	this->copyValuesInto(clonedArray);

	for (unsigned i = 0; i < this->_length; i++) {
		clonedArray->_storage[i] = this->at(i);
	}

	return clonedArray;
}