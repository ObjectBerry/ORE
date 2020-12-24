#pragma once
namespace Memory {
	class MemoryAllocator;
}
namespace Object_Layout {
	class ObjectMap;
}


namespace Objects {
	class Object {
		Object_Layout::ObjectMap* _objectMap;
		Object** _slotValues;

	protected:
		void* operator new(size_t size, Memory::MemoryAllocator* memoryAllocator);
		Object(Memory::MemoryAllocator* memoryAllocator, Object_Layout::ObjectMap* objectMap);
	
	public:
		static Object* create(Memory::MemoryAllocator* memoryAllocator, Object_Layout::ObjectMap* objectMap);
		
		


	};
}