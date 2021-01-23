#pragma once
#include "ByteArray.hpp"

#include "SymbolType.hpp"

namespace Objects {
	
	/* Symbol is used as name for slots and as parameters in some primitives
	// It have unique ability - it can be cached (TODO:: Implement object cache as dependency injection)
	// Using cache , we can enforce that two symbols with same values are identical
	*///
	class Symbol : public Objects::ByteArray {
		Objects::SymbolType _symbolType;
		unsigned short		_parameterCount;

	protected:
		Symbol(basicParameter, char* characters, Objects::SymbolType symbolType, unsigned short parameterCount);

	public:
		static Objects::Symbol* create(basicParameter, char* characters, Objects::SymbolType symbolType, unsigned short parameterCount);
		Objects::Symbol*		clone(Memory::MemoryAllocator* memoryAllocator /*Add cache here*/);
		
	public:
		bool	equalObject(Objects::Symbol* other);
		bool	equalValue(const char* characters, Objects::SymbolType symbolType, unsigned short parameterCount);
		
		inline SymbolType		getSymbolType() { return this->_symbolType; };
		inline unsigned short	getSymbolParameters() { return this->_parameterCount; };
	public:
		OBJECT_TYPE(ObjectType::Symbol);
	};
}

