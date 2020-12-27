#pragma once
#include "Object.hpp"

namespace Objects {
	class ByteArray : public Objects::Object {
		unsigned short _length;
		char* _storage;

	protected:

		ByteArray(basicParameter, unsigned short length);
		ByteArray(basicParameter, char* characters);
	public:
		static ByteArray* create(basicParameter, unsigned short length);

		ByteArray* clone(Memory::MemoryAllocator* allocator);
	
	public:
		inline char at(unsigned short index) { return this->_storage[index]; };
		inline void atPut(unsigned short index, char value) { this->_storage[index] = value; };

		inline unsigned short getArrayLength() { return this->_length; };
		inline char* getArrayStorage() { return this->_storage; };
	public:
		OBJECT_TYPE(ObjectType::ByteArray);
	};
}