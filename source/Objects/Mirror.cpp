#include "Mirror.hpp"


Objects::Mirror::Mirror(basicParameter, Objects::Object* reflectee) : Objects::Object(memoryAllocator, objectMap) {
	this->_reflectee = reflectee;
}
Objects::Mirror::Mirror(Object_Layout::ObjectMap* objectMap, Objects::Object* reflectee) : Objects::Object(objectMap) {
	this->_reflectee = reflectee;
}

Objects::Mirror* Objects::Mirror::create(basicParameter, Objects::Object* reflectee) {
	return new(memoryAllocator) Objects::Mirror(memoryAllocator, objectMap, reflectee);
}

Objects::Mirror* Objects::Mirror::clone(Memory::MemoryAllocator* allocator) {
	return Objects::Mirror::create(allocator, this->getObjectMap(), this->_reflectee);
}
