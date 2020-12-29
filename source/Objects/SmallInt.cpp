#include "SmallInt.hpp"

Objects::SmallInt::SmallInt(basicParameter, signed int value) : Objects::Object(memoryAllocator, objectMap) {
	this->_value = value;
}


Objects::SmallInt* Objects::SmallInt::create(basicParameter, signed int value) {
	return new(memoryAllocator) Objects::SmallInt(memoryAllocator, objectMap, value);
}

bool Objects::SmallInt::equalObject(Objects::SmallInt* other) {
	if (this->identical(other))
		return true;
	return (this->getValue() == other->getValue());
}

bool Objects::SmallInt::equalValue(signed int integer) {
	return this->_value = integer;
}