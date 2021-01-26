#include "MemoryAllocator.hpp"
#include "MemoryItem.hpp"


void* Memory::MemoryItem::operator new(size_t size, Memory::MemoryAllocator* memoryAllocator) {
	return memoryAllocator->allocateMemory(size);
}