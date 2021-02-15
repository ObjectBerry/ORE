#include "../Object_Layout/MethodMap.hpp"
#include "../Object_Layout/ObjectMap.hpp"
#include "MappedObject.hpp"


Objects::MappedObject::MappedObject(Object_Layout::ObjectMap* objectMap) {
	this->_visitedObject = false;
	this->_objectType = Objects::ObjectType::MappedObject;

	this->_objectMap = objectMap;
}

Objects::MappedObject* Objects::MappedObject::clone(Memory::MemoryAllocator* allocator) {
	return new(allocator) Objects::MappedObject(this->getObjectMap());
}


// Map getters
unsigned short Objects::MappedObject::getSlotCount() {
	return this->getObjectMap()->getSlotCount();
}

bool Objects::MappedObject::hasCode() {
	return this->_objectMap->hasCode();
}
unsigned short Objects::MappedObject::getParameterCount() {
	if (not this->_objectMap->hasCode()) {
		return 0;
	}
	if (this->_objectType == Objects::ObjectType::Assignment) {
		return 1;
	}
	return reinterpret_cast<Object_Layout::MethodMap*>(this->_objectMap)->getParameterCount();
}

Objects::ByteArray* Objects::MappedObject::getBytecode() {
	if (not this->_objectMap->hasCode())
		return nullptr;

	return reinterpret_cast<Object_Layout::MethodMap*>(this->_objectMap)->getBytecode();
}

Objects::ObjectArray* Objects::MappedObject::getLiterals() {
	if (not this->_objectMap->hasCode())
		return nullptr;

	return reinterpret_cast<Object_Layout::MethodMap*>(this->_objectMap)->getLiterals();
}