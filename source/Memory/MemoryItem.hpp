#pragma once
namespace Memory {
	class MemoryAllocator;
}
namespace Memory {
	/* This is MemoryItem - it is base for all memory items that are chcecked during garbage collection
	// It will contain important info for garbage collector and object memory
	*/
	class MemoryItem {
	private:
		
		size_t						_itemSize;
		Memory::MemoryAllocator*	_itemAllocator;

	public:
		void* operator new(size_t size, Memory::MemoryAllocator* memoryAllocator);
		void operator delete(void* pointer);

	public:
		inline size_t					getSize(){ return this->_itemSize; };
		inline Memory::MemoryAllocator* getAllocator() { return this->_itemAllocator; };

	private:
		virtual void methodToForceCreationOfVTable() {};
	};
}