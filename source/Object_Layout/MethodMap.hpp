#pragma once
#include "ObjectMap.hpp"

namespace Objects {
	class ByteArray;
	class ObjectArray;
	
}
namespace Object_Layout {
	enum class ScopeType : unsigned char {
		Undefined	= 0x00,
		Lexical		= 0x01,
		Dynamic		= 0x02,
	};
	enum class ReturnType : unsigned char {
		Undefined	= 0x00,
		Normal		= 0x01,
		Implicit	= 0x02,
	};

	class MethodMap : public Object_Layout::ObjectMap {
		Objects::ByteArray*		_bytecode;
		Objects::ObjectArray*	_literals;
		unsigned short			_parameterCount;
		ScopeType				_scopeType;
		ReturnType				_returnType;

	private:
		MethodMap(Memory::MemoryAllocator* allocator, unsigned short slotCount, Objects::ByteArray* bytecode, Objects::ObjectArray* literals, ScopeType scopeType, ReturnType returnType);

	public:
		static MethodMap* create(Memory::MemoryAllocator* allocator, unsigned short slotCount, Objects::ByteArray* bytecode, Objects::ObjectArray* literals, ScopeType scopeType, ReturnType returnType);
		MethodMap* clone(Memory::MemoryAllocator* allocator);


	public:
		void setDescription(unsigned short index, SlotDescription slotDescription);
		bool hasCode() { return true; }

		inline Objects::ByteArray*		getBytecode() { return this->_bytecode; }
		inline Objects::ObjectArray*	getLiterals() { return this->_literals; }
		inline unsigned short			getParameterCount() { return this->_parameterCount; };
		inline ScopeType				getScopeType() { return this->_scopeType; };
		inline ReturnType				getReturnType() { return this->_returnType; };
	};
}