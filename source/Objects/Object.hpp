#pragma once
#include "ObjectType.hpp"

namespace Memory {
	class MemoryAllocator;
}
namespace Object_Layout {
	class ObjectMap;
}

// this is used to return type of object - just replace 'name' with enum type
#define OBJECT_TYPE(name) inline Objects::ObjectType getType() {return name;}

// this is used to define first two arguments of constructor and factory method
#define basicParameter Memory::MemoryAllocator* allocator, Object_Layout::ObjectMap* objectMap

namespace Objects {
	class Object {
		Object_Layout::ObjectMap* _objectMap;
		Object** _slotValues;

	protected:
		void* operator new(size_t size, Memory::MemoryAllocator* memoryAllocator);
		Object(basicParameter);
	
	public:
		static Object* create(Memory::MemoryAllocator* memoryAllocator, Object_Layout::ObjectMap* objectMap);
		
		Object* clone(Memory::MemoryAllocator* allocator);
		void copyValuesInto(Object* target);

	public:
		// Object access methods
		inline Object* getValue(unsigned short index) { return this->_slotValues[index]; };
		inline void setValue(unsigned short index, Object* value) { this->_slotValues[index] = value; };
	
	public:
		OBJECT_TYPE(ObjectType::Object);
	};
}