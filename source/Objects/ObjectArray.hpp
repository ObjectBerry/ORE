#pragma once
#include "Object.hpp"

namespace Objects {
	class ObjectArray : public Objects::Object {
		unsigned short		_length;
		Objects::Object**	_storage;
		
		ObjectArray(basicParameter, unsigned short length);

	public:
		static ObjectArray* create(basicParameter, unsigned short length);
		ObjectArray* clone(Memory::MemoryAllocator* allocator);

	public:
		inline Objects::Object* at(unsigned short index) { 
			return this->_storage[index];
		};
		inline void				atPut(unsigned short index, Objects::Object* value) {
			this->_storage[index] = value; 
		};

		inline unsigned short		getArrayLength() { return this->_length; };
		inline Objects::Object**	getArrayStorage() { return this->_storage; };
	public:
		OBJECT_TYPE(ObjectType::ByteArray);
	};
}