#pragma once
#include "MemoryAllocator.hpp"

namespace Memory {
	// This is native allocator - it is using malloc function from <stdlib.h>
	// It is used only during testing as replacement for object space
	class NativeAllocator : public MemoryAllocator {
	public:
		void* allocateMemory(size_t size);
		char* allocateBytes(size_t count);

	};
}
