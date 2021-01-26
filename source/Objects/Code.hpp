#pragma once
#include "Object.hpp"

namespace Objects {
	class ObjectArray;
	class ByteArray;
}

namespace Objects {

	/* Code object is used as representation for method code
	// It contains array for bytecodes and array for literal
	// Both arrays are represented as ORE Objects and thus they can be manipulated throught primitives
	// 
	// INFO: This object is deprecated and it will be removed - dont use it 
	*/
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
	
	public:
		OBJECT_TYPE(ObjectType::Code);
	
	};
}