#include <stdlib.h>

#include "NativeAllocator.hpp"

Memory::NativeAllocator::NativeAllocator(): _allocatedBytes(0), _allocatedMemory(0) {};

void* Memory::NativeAllocator::allocateMemory(size_t size) {
	this->_allocatedMemory += size;
	return malloc(size);
}
char* Memory::NativeAllocator::allocateBytes(size_t count) {
	this->_allocatedBytes += count;
	return static_cast<char*>(malloc(count));
}
