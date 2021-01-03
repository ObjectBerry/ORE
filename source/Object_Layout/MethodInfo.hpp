#pragma once
namespace Memory {
	class MemoryAllocator;
}
namespace Object_Layout {
	enum class ScopeType : unsigned short {
		Lexical,
		Dynamic
	};
	enum class ReturnType : unsigned short {
		Normal,
		Implicit,
	};

	/* This is used as holder of informations about method
	// It is storing info about objects with code - their scope type and if they can use implicit return
	// If object map doesnt have code , pointer will be empty
	*///
	class MethodInfo {
		Object_Layout::ScopeType _scopeType;
		Object_Layout::ReturnType _returnType;
	public:
		MethodInfo();
		MethodInfo(Object_Layout::ScopeType scopeType, Object_Layout::ReturnType returnType);

		void* operator new(size_t size, Memory::MemoryAllocator* allocator);
		

		bool isLexical() { return this->_scopeType == ScopeType::Lexical; };
		bool isImplicit() { return this->_returnType == ReturnType::Implicit; };
	};
	
}