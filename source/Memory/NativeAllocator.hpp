#pragma once
#include "MemoryAllocator.hpp"

namespace Memory {
	/* This is native allocator - it is using malloc function from <stdlib.h>
	// It is used only during testing as replacement for object space
	// It also contain memory counter  
	*///
	class NativeAllocator : public MemoryAllocator {
		unsigned int _allocatedMemory;
		unsigned int _allocatedBytes;
		
		unsigned int	_bufferSize;
		char*			_buffer;
		char*			_bufferPointer;

	public:
		NativeAllocator(unsigned int bufferSize);
		~NativeAllocator();
		
		void* allocateMemory(size_t size);
		char* allocateBytes(size_t count);

	};
}
