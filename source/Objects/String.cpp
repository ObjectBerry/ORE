#include "String.hpp"

Objects::String::String(Object_Layout::ObjectMap* objectMap, const char* characters) : Objects::ByteArray(objectMap, characters) {
	this->_objectType = Objects::ObjectType::String;
};



Objects::String* Objects::String::clone(Memory::MemoryAllocator* allocator) {
	return  reinterpret_cast<Objects::String*>(ByteArray::clone(allocator)); // we will use clone method from byte array
}

bool Objects::String::equalObject(Objects::String* other) {
	if (other->getArrayLength() != this->getArrayLength())
		return false;

	for (unsigned i = 0; i < this->getArrayLength(); i++) {
		if (this->at(i) != other->at(i)) {
			return false;
		}
	}

	return true;
}

bool Objects::String::equalValue(const char* characters) {
	unsigned short length = 0;
	while (characters[length] != '\0')
		length++;
	length++;

	if (this->getArrayLength() != length)
		return false;

	for (unsigned i = 0; i < this->getArrayLength(); i++) {
		if (this->at(i) != characters[i]) {
			return false;
		}
	}

	return true;
}