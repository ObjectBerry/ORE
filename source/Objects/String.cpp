#include "String.hpp"

Objects::String::String(basicParameter, const char* characters) : Objects::ByteArray(memoryAllocator, objectMap, (char*)characters) {}

Objects::String* Objects::String::create(basicParameter, const char* characters) {
	return new(memoryAllocator) Objects::String(memoryAllocator, objectMap, characters);
}

Objects::String* Objects::String::clone(Memory::MemoryAllocator* allocator) {
	return this->clone(allocator); // we will use clone method from byte array
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