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
Objects::Symbol* Objects::Symbol::clone(Memory::MemoryAllocator* memoryAllocator) {
	Objects::Symbol* clonnedSymbol = Objects::Symbol::create(
		memoryAllocator,
		this->getObjectMap(),
		this->getArrayStorage(),
		this->_symbolType,
		this->_parameterCount
	);
	return clonnedSymbol;
}


bool Objects::Symbol::equalObject(Objects::Symbol* other) {
	if (this->identical(other)) {
		return true;
	}
	if (this->_symbolType != other->_symbolType)
		return false;
	if (this->_parameterCount != other->_parameterCount)
		return false;

	if (this->getArrayLength() != other->getArrayLength())
		return false;

	for (unsigned i = 0; i < this->getArrayLength(); i++) {
		if (this->at(i) != other->at(i)) {
			return false;
		}
	}
	return true;
}

bool Objects::Symbol::equalValue(char* characters, Objects::SymbolType symbolType, unsigned short parameterCount) {
	if (this->_symbolType != symbolType)
		return false;
	if (this->_parameterCount != parameterCount)
		return false;

	unsigned short length = 0;
	while (characters[length] != '\0')
		length++;
	length++;

	if (this->getArrayLength() != length)
		return false;
	
	for (unsigned i = 0; i < this->getArrayLength(); i++) {
		if (this->at(i) != characters[i]) {
			return false;
		}
	}
	return true;
}