#pragma once
#include "ByteArray.hpp"

#include "SymbolType.hpp"

namespace Objects {
	
	/* Symbol is special object that have important role in ORE
	// It is used as:
	//   + name of slot 
	//   + message names (only symbol can be message selector)
	//   + parameter of primitives 
	// TODO: Implement caching for this object - it will increase performance
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

