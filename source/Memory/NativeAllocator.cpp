#include <stdlib.h>

#include "NativeAllocator.hpp"

void* Memory::NativeAllocator::allocateMemory(size_t size) {
	return malloc(size);
}
char* Memory::NativeAllocator::allocateBytes(size_t count) {
	return static_cast<char*>(malloc(count));
}
