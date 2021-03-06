#pragma once
#include "SlotObject.hpp"

namespace Objects {

	/* Byte Array is object for byte operations
	// It is supposed to store , access and assign bytes into byte array
	// Byte array is allocated by different method than other items in memory
	*///
	class ByteArray : public Objects::SlotObject {
		unsigned short _length;
		char* _storage;

	
	public:
		ByteArray(Object_Layout::ObjectMap* objectMap, unsigned short length);
		ByteArray(Object_Layout::ObjectMap* objectMap, const char* characters);
		virtual ByteArray*	clone(Memory::MemoryAllocator* allocator);
		virtual ByteArray* cloneResize(Memory::MemoryAllocator* allocator, unsigned short newLength);
	
	public:
		inline char				at(unsigned short index) { return this->_storage[index]; };
		inline void				atPut(unsigned short index, char value) { this->_storage[index] = value; };
		inline unsigned short	getArrayLength() { return this->_length; };
		inline char*			getArrayStorage() { return this->_storage; };
	};
}