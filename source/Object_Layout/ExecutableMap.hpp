#pragma once
#include "ObjectMap.hpp"

namespace Objects {
	class ByteArray;
	class ObjectArray;
	
}
namespace Object_Layout {
	enum class ScopeType : unsigned char {
		Lexical,
		Dynamic
	};
	enum class ReturnType : unsigned char {
		Normal,
		Implicit,
	};

	class ExecutableMap : public Object_Layout::ObjectMap {
		Objects::ByteArray*		_bytecode;
		Objects::ObjectArray*	_literals;
		unsigned short			_parameterCount;
		ScopeType				_scopeType;
		ReturnType				_returnType;

	private:
		ExecutableMap(Memory::MemoryAllocator* allocator, unsigned short slotCount, Objects::ByteArray* bytecode, Objects::ObjectArray* literals, ScopeType scopeType, ReturnType returnType);

	public:
		static ExecutableMap* create(Memory::MemoryAllocator* allocator, unsigned short slotCount, Objects::ByteArray* bytecode, Objects::ObjectArray* literals, ScopeType scopeType, ReturnType returnType);
		ExecutableMap* clone(Memory::MemoryAllocator* allocator);


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