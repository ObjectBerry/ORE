#pragma once
#include "MemoryAllocator.hpp"

namespace Memory {
	class NativeAllocator : public Memory::MemoryAllocator {
	public:
		void* allocateMemory(size_t size);
		char* allocateBytes(size_t count);
	};
}