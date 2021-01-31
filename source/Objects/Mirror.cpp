#include "Mirror.hpp"


Objects::Mirror::Mirror(basicParameter, Objects::Object* reflectee) : Objects::Object(memoryAllocator, objectMap) {
	this->reflectee = reflectee;
}

Objects::Mirror* Objects::Mirror::create(basicParameter, Objects::Object* reflectee) {
	return new(memoryAllocator) Objects::Mirror(memoryAllocator, objectMap, reflectee);
}

Objects::Mirror* Objects::Mirror::clone(Memory::MemoryAllocator* allocator) {
	return Objects::Mirror::create(allocator, this->getObjectMap(), this->reflectee);
}
