#include "Symbol.hpp"

#include "Assignment.hpp"

Objects::Assignment::Assignment(basicParameter, Objects::Symbol* associatedSlot) : Objects::Object(memoryAllocator, objectMap) {
	this->_associatedSlot = associatedSlot;
}

Objects::Assignment* Objects::Assignment::create(basicParameter, Objects::Symbol* associatedSlot) {
	return new(memoryAllocator) Objects::Assignment(memoryAllocator, objectMap, associatedSlot);
}

Objects::Assignment* Objects::Assignment::clone(Memory::MemoryAllocator* allocator) {
	return Objects::Assignment::create(allocator, this->getObjectMap(), this->_associatedSlot);
}