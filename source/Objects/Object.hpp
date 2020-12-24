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
		
		Object* clone(Memory::MemoryAllocator* allocator);
		void copyValuesInto(Object* target);

	public:
		// Object access methods
		inline Object* getValue(unsigned short index) { return this->_slotValues[index]; };
		inline void setValue(unsigned short index, Object* value) { this->_slotValues[index] = value; };
	};
}