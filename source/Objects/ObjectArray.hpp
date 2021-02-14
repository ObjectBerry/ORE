#pragma once
#include "SlotObject.hpp"

namespace Objects {

	/* SlotObject array is representation for array of pointers.
	// It allows access using index and manipulation of objects stored in array
	*///
	class ObjectArray : public Objects::SlotObject {
		unsigned short		_length;
		Objects::SlotObject**	_storage;
		

	public:
		ObjectArray(Object_Layout::ObjectMap* objectMap, unsigned short length);
		virtual ObjectArray* clone(Memory::MemoryAllocator* allocator);
		virtual ObjectArray* cloneResize(Memory::MemoryAllocator* allocator, unsigned short newLength);

	public:
		inline Objects::SlotObject* at(unsigned short index) { 
			return this->_storage[index];
		};
		inline void				atPut(unsigned short index, Objects::SlotObject* value) {
			this->_storage[index] = value; 
		};

		inline unsigned short		getArrayLength() { return this->_length; };
		inline Objects::SlotObject**	getArrayStorage() { return this->_storage; };

	};
}