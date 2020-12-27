#include "Symbol.hpp"

Objects::Symbol::Symbol(basicParameter, char* characters, Objects::SymbolType symbolType, unsigned short parameterCount) : Objects::ByteArray(memoryAllocator, objectMap, characters) {
	this->_symbolType = symbolType;
	this->_parameterCount = parameterCount;
}

Objects::Symbol* Objects::Symbol::create(basicParameter, char* characters, Objects::SymbolType symbolType, unsigned short parameterCount) {
	// we will add symbol cache later.
	// For now we will create new symbol and we will compare values of symbols (too slow)
	return new (memoryAllocator) Symbol(memoryAllocator, objectMap, characters, symbolType, parameterCount);
}
