#include "../Memory/MemoryAllocator.hpp"


#include "../Objects/Code.hpp"

#include "SlotDescription.hpp"
#include "ExecutableMap.hpp"

Object_Layout::ExecutableMap::ExecutableMap(Memory::MemoryAllocator* allocator, unsigned short slotCount, Objects::Code* objectCode, ScopeType scopeType, ReturnType returnType) : Object_Layout::ObjectMap(allocator, slotCount) {
	this->_objectCode = objectCode;
	this->_parameterCount = 0;
	this->_scopeType = scopeType;
	this->_returnType = returnType;
}

Object_Layout::ExecutableMap* Object_Layout::ExecutableMap::create(Memory::MemoryAllocator* allocator, unsigned short slotCount, Objects::Code* objectCode, ScopeType scopeType, ReturnType returnType) {
	return new(allocator) Object_Layout::ExecutableMap(allocator, slotCount, objectCode, scopeType, returnType); 
};

Object_Layout::ExecutableMap* Object_Layout::ExecutableMap::clone(Memory::MemoryAllocator* allocator) {
	Object_Layout::ExecutableMap* clonnedMap = Object_Layout::ExecutableMap::create(
		allocator,
		this->getSlotCount(),
		this->_objectCode->clone(allocator),
		this->_scopeType,
		this->_returnType
	);

	for (unsigned i = 0; i < this->getSlotCount(); i++) {
		clonnedMap->_slotDescriptions[i] = this->_slotDescriptions[i];
	}
}