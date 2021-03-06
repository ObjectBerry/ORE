#include "SmallInt.hpp"


Objects::SmallInt::SmallInt(Object_Layout::ObjectMap* objectMap, signed int value) : Objects::SlotObject(objectMap) {
	this->_value = value;

	this->_objectType = Objects::ObjectType::SmallInt;
}

Objects::SmallInt* Objects::SmallInt::clone(Memory::MemoryAllocator* allocator) {
	return new(allocator) Objects::SmallInt(
		this->getObjectMap(),
		this->_value
	);
}

bool Objects::SmallInt::equalObject(Objects::SmallInt* other) {
	if (this->identical(other))
		return true;
	return (this->getValue() == other->getValue());
}

bool Objects::SmallInt::equalValue(signed int integer) {
	return this->_value = integer;
}