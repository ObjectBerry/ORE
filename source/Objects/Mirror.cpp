#include "Mirror.hpp"



Objects::Mirror::Mirror(Object_Layout::ObjectMap* objectMap, Objects::Object* reflectee) : Objects::Object(objectMap) {
	this->_reflectee = reflectee;
}
Objects::Mirror* Objects::Mirror::clone(Memory::MemoryAllocator* allocator) {
	return new(allocator) Objects::Mirror( this->getObjectMap(), this->_reflectee);
}
