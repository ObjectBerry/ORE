#include "MemoryAllocator.hpp"
#include "MemoryItem.hpp"


void* Memory::MemoryItem::operator new(size_t size, Memory::MemoryAllocator* memoryAllocator) {
	void* newItem = static_cast<Memory::MemoryItem*>(memoryAllocator->allocateMemory(size));
	
	((Memory::MemoryItem*)newItem)->_itemSize		= size;
	((Memory::MemoryItem*)newItem)->_itemAllocator	= memoryAllocator;
	
	return newItem;
}
void Memory::MemoryItem::operator delete(void* pointer) {
	return; // empty function , dont use it
}