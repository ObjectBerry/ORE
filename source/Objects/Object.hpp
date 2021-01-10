#pragma once
#include "ObjectType.hpp"
#include "../Memory/MemoryAllocator.hpp"

namespace Memory {
	class MemoryAllocator;
}
namespace Object_Layout {
	class ObjectMap;
}
namespace Objects {
	class Symbol;
}

// this is used to return type of object - just replace 'name' with enum type
#define OBJECT_TYPE(name) inline Objects::ObjectType getType() {return name;}

// this is used to define first two arguments of constructor and factory method
#define basicParameter Memory::MemoryAllocator* memoryAllocator, Object_Layout::ObjectMap* objectMap

namespace Objects {

	/* This is basic entity of object system.
	// It contain pointer to map and pointer to slot values.
	// It allows to change slot values using method setValue(...) and getValue(...)
	// Clonning doesnt clone map itself - instead , it share it and new object will have same map as old one
	*///
	class Object {
		bool						_visitedObject; // used during message sending
		Object_Layout::ObjectMap*	_objectMap;
		Object**					_slotValues;

	protected:
		void* operator new(size_t size, Memory::MemoryAllocator* memoryAllocator);
		Object(basicParameter);
	
	public:
		static Object*			create(basicParameter);
		static Object*			createWithMap(Memory::MemoryAllocator* allocator, unsigned short slotCount);
		Object*					clone(Memory::MemoryAllocator* allocator);
		void					copyValuesInto(Object* target);

	public:
		// Object access methods for value storage
		inline Object_Layout::ObjectMap* getObjectMap() { return this->_objectMap; };
		inline Object*			getValue(unsigned short index) { return this->_slotValues[index]; };
		inline void				setValue(unsigned short index, Object* value) { this->_slotValues[index] = value; };
		
	public:
		// Object slot access 
		Objects::Object*		getSlot(Objects::Symbol* slotName);
		bool					setSlot(Objects::Symbol* slotName, Objects::Object* reference);
	
		inline void				setVisitedObject(bool visitedValue) { this->_visitedObject = visitedValue; };
		inline bool				getVisitedObject()					{ return this->_visitedObject; };
	public:
		inline bool				identical(Objects::Object* other) { return this == other; };
	
	public:
		OBJECT_TYPE(ObjectType::Object);
	};
}