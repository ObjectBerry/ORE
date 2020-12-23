#pragma once

namespace Memory {
	// This is class used as facade between allocator itself and objects that need memory
	// Too implement own facade , use this class as parent and override methods
	class MemoryFacade {
		virtual void* allocateMemory(size_t size) = 0;
	};
}