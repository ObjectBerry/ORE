

#include "../Memory/MemoryFacade.hpp"
#include "Object.hpp"

void* Objects::Object::operator new(size_t size, Memory::MemoryFacade* memoryFacade) {
	return memoryFacade->allocate(size);
}