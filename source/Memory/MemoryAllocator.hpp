#pragma once

namespace Memory {
	/* This is class used as facade between memory itself and objects that need memory
	// Use this class as parent and override methods if you want implement own allocator
	*///
	class MemoryAllocator {
	public:
		virtual void* allocateMemory(size_t size) = 0;
		virtual char* allocateBytes(size_t count) = 0;
	};
}