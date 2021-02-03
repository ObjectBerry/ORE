#include "../Memory/MemoryAllocator.hpp"


#include "../Objects/ByteArray.hpp"
#include "../Objects/ObjectArray.hpp"

#include "SlotDescription.hpp"
#include "MethodMap.hpp"


Object_Layout::MethodMap::MethodMap(unsigned short slotCount, Objects::ByteArray* bytecode, Objects::ObjectArray* literals, ScopeType scopeType, ReturnType returnType) : Object_Layout::ObjectMap(slotCount) {
	this->_bytecode = bytecode;
	this->_literals = literals;
	this->_parameterCount = 0;
	this->_scopeType = scopeType;
	this->_returnType = returnType;
}


Object_Layout::MethodMap* Object_Layout::MethodMap::clone(Memory::MemoryAllocator* allocator) {
	Object_Layout::MethodMap* clonnedMap = new(allocator) Object_Layout::MethodMap(
		this->getSlotCount(),
		this->_bytecode->clone(allocator),
		this->_literals->clone(allocator),
		this->_scopeType,
		this->_returnType
	);

	for (unsigned i = 0; i < this->getSlotCount(); i++) {
		clonnedMap->_slotDescriptions[i] = this->_slotDescriptions[i];
	}
	clonnedMap->_parameterCount = this->getParameterCount();
	return clonnedMap;
}

void Object_Layout::MethodMap::setDescription(unsigned short index, Object_Layout::SlotDescription slotDescription) {
	if (this->_slotDescriptions[index].isParameter()) {
		this->_parameterCount--;
	}
	if (slotDescription.isParameter()) {
		this->_parameterCount++;
	}
	
	this->_slotDescriptions[index] = slotDescription;
}

void Object_Layout::MethodMap::setCodeDescription(Objects::ByteArray* bytecode, Objects::ObjectArray* literals, ScopeType scopeType, ReturnType returnType) {
	this->_bytecode		= bytecode;
	this->_literals		= literals;
	this->_scopeType	= scopeType;
	this->_returnType	= returnType;
}
