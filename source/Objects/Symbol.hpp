#pragma once
#include "ByteArray.hpp"

#include "SymbolType.hpp"

namespace Objects {
	
	class Symbol : public Objects::ByteArray {
		Objects::SymbolType _symbolType;
		unsigned short		_parameterCount;

	protected:
		Symbol(basicParameter, char* characters, Objects::SymbolType symbolType, unsigned short parameterCount);

	public:
		static Objects::Symbol* create(basicParameter, char* characters, Objects::SymbolType symbolType, unsigned short parameterCount);
	};
}

