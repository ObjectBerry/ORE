#include <stdlib.h>

#include "BufferAllocator.hpp"

Memory::BufferAllocator::BufferAllocator(unsigned int bufferSize) {
	this->_allocatedBytes = 0;
	this->_allocatedMemory = 0;

	this->_bufferSize = bufferSize;
	this->_buffer = new char[bufferSize];
	this->_bufferPointer = _buffer;
};
Memory::BufferAllocator::~BufferAllocator() {
	delete[] this->_buffer;
}

void* Memory::BufferAllocator::allocateMemory(size_t size) {
	void* pointer = static_cast<void*>(this->_bufferPointer);
	this->_allocatedMemory += size;
	this->_bufferPointer += size;
	return pointer;
}
char* Memory::BufferAllocator::allocateBytes(size_t count) {
	char* bytes = (this->_bufferPointer);
	this->_allocatedMemory += count;
	this->_bufferPointer += count;
	return bytes;
}
