#pragma once
namespace Memory {
	class MemoryAllocator;
}
namespace Memory {
	/* This is MemoryItem - it is base for all memory items that are chcecked during garbage collection
	// It will contain important info for garbage collector and object memory
	*/
	class MemoryItem {
	protected:
		void*						_emptyPointer; // place for vtable
		size_t						_itemSize;
		Memory::MemoryAllocator*	_itemAllocator;

	public:
		void* operator new(size_t size, Memory::MemoryAllocator* memoryAllocator);

	};
}