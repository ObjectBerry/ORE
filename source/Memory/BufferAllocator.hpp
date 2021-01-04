#pragma once
#include "MemoryAllocator.hpp"

namespace Memory {
	/* This is native allocator - it is using malloc function from <stdlib.h>
	// It is used only during testing as replacement for object space
	// It also contain memory counter  
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
