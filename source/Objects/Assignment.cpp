#include "Symbol.hpp"

#include "Assignment.hpp"



Objects::Assignment::Assignment(Object_Layout::ObjectMap* objectMap, Objects::Symbol* associatedSlot) : Objects::SlotObject(objectMap) {
	this->_associatedSlot = associatedSlot;
	this->_objectType = Objects::ObjectType::Assignment;
}
Objects::Assignment* Objects::Assignment::clone(Memory::MemoryAllocator* allocator) {
	return new(allocator) Objects::Assignment( this->getObjectMap(), this->_associatedSlot);
}