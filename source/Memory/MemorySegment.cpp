
#include "MemorySegment.hpp"

Memory::MemorySegment::MemorySegment(unsigned short bufferSize) {
	this->_bufferSize = bufferSize;
	this->_buffer = new char[bufferSize];
	this->_bufferForwardPointer = this->_buffer;
	this->_bufferBackwardPointer = (this->_buffer + bufferSize);

	this->resetBuffer();
}

Memory::MemorySegment::~MemorySegment() {
	delete[] this->_buffer;
}

void Memory::MemorySegment::resetBuffer() {
	for (unsigned i = 0; i < this->_bufferSize; i++) {
		this->_buffer[i] = 0;
	}
}

bool Memory::MemorySegment::isLimit(size_t size) {
	unsigned short limit = static_cast<unsigned short>(static_cast<float>(this->_bufferSize) * 0.2);
	int free = this->_bufferBackwardPointer - this->_bufferForwardPointer;
	int avalibe = free - size;

	return limit > avalibe;
}

void* Memory::MemorySegment::allocateMemory(size_t size, bool fromEnd) {
	if (isLimit(size)) {
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
