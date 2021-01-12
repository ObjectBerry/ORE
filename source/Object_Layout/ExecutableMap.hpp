#pragma once
#include "ObjectMap.hpp"


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
		Objects::Code* _objectCode;
		unsigned short _parameterCount;
		ScopeType      _scopeType;
		ReturnType     _returnType;

	private:
		ExecutableMap(Memory::MemoryAllocator* allocator, unsigned short slotCount, Objects::Code* objectCode, ScopeType scopeType, ReturnType returnType);

	public:
		ExecutableMap* create(Memory::MemoryAllocator* allocator, unsigned short slotCount, Objects::Code* objectCode, ScopeType scopeType, ReturnType returnType);
		ExecutableMap* clone(Memory::MemoryAllocator* allocator);


	public:
		bool hasCode() { return true; }
	};
}