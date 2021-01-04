
#include "MemorySpace.hpp"

Memory::MemorySpace::MemorySpace(unsigned short bufferSize) {
	this->_bufferSize = bufferSize;
	this->_buffer = new char[bufferSize];
	this->_bufferForwardPointer = this->_buffer;
	this->_bufferBackwardPointer = (this->_buffer + bufferSize);
}

Memory::MemorySpace::~MemorySpace() {
	delete[] this->_buffer;
}

void* Memory::MemorySpace::allocateMemory(size_t size, bool fromEnd) {
	if ((this->_bufferForwardPointer - this->_bufferBackwardPointer) - size < 100) {
		return nullptr;
	}

	char* newItem = nullptr;
	if (fromEnd) {
		this->_bufferBackwardPointer -= size;
		newItem = this->_bufferBackwardPointer;
	}
	else {
		newItem = this->_bufferForwardPointer;
		this->_bufferForwardPointer += size;
	}

	return newItem;
}
