#include "../Memory/MemoryFacade.hpp"
#include "../Object_Layout/ObjectMap.hpp"

#include "Object.hpp"

void* Objects::Object::operator new(size_t size, Memory::MemoryFacade* memoryFacade) {
	return memoryFacade->allocate(size);
}

Objects::Object::Object(Memory::MemoryFacade* memoryFacade, Object_Layout::ObjectMap* objectMap) {
	this->_objectMap = objectMap;
	this->_slotValues = static_cast<Object**>( memoryFacade->allocate(sizeof(Object*) * objectMap->getSlotCount()));
}

// factory method - use this to create bare objects
Objects::Object* Objects::Object::create(Memory::MemoryFacade* memoryFacade, Object_Layout::ObjectMap* objectMap) {
	return new(memoryFacade) Objects::Object(memoryFacade, objectMap);
}