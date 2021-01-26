#pragma once
#include "MemoryAllocator.hpp"

namespace Memory {
	/* This is buffer allocator - it is ussing preallocated buffer to store objects
	// Buffer have fixed size and it cant be resized 
	// Use this during development and testing - dont forget to call destructor to destroy all allocated objects
	*///
	class BufferAllocator : public MemoryAllocator {
		unsigned int _allocatedMemory;
		unsigned int _allocatedBytes;
		
		unsigned int	_bufferSize;
		char*			_buffer;
		char*			_bufferPointer;

	public:
		BufferAllocator(unsigned int bufferSize);
		~BufferAllocator();
		
		void* allocateMemory(size_t size);
		char* allocateBytes(size_t count);

	};
}
