#pragma once
#include "Object.hpp"

namespace Objects {
	class ObjectArray;
	class ByteArray;
}

namespace Objects {
	class Code : public	Objects::Object {
		Objects::ByteArray*		_bytecode;
		Objects::ObjectArray*	_literals;

	private:
		Code(basicParameter, Objects::ByteArray* bytecode, Objects::ObjectArray* literals);

	public:
		static Code* create(basicParameter, Objects::ByteArray* bytecode, Objects::ObjectArray* literals);
		Code* clone(Memory::MemoryAllocator* allocator);

	public:
		inline Objects::ByteArray* getBytecode() { return this->_bytecode; };
		inline Objects::ObjectArray* getLiterals() { return this->_literals; };
	};
}