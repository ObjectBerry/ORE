#pragma once
#include "MemoryAllocator.hpp"

namespace Memory {
	/* This is native allocator
	// When we request memory , it will just call malloc - that is all 
	// TODO: Implement list soo we will be able to free objects after destruction of allocator
	*/
	class NativeAllocator : public Memory::MemoryAllocator {
	public:
		void* allocateMemory(size_t size);
		char* allocateBytes(size_t count);
	};
}