#pragma once
namespace Memory {
	class MemoryAllocator;
}
namespace Memory {
	class MemoryItem {
	public:
		void* operator new(size_t size, Memory::MemoryAllocator* memoryAllocator);

	};
}