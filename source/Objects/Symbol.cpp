#include "Symbol.hpp"


Objects::Symbol::Symbol(Object_Layout::ObjectMap* objectMap, const char* characters, Objects::SymbolType symbolType, unsigned short parameterCount) : Objects::ByteArray(objectMap, characters) {
	this->_symbolType		= symbolType;
	this->_parameterCount	= parameterCount;

	this->_objectType = Objects::ObjectType::Symbol;
}


Objects::Symbol* Objects::Symbol::clone(Memory::MemoryAllocator* memoryAllocator) {
	Objects::Symbol* clonnedSymbol = new(memoryAllocator) Objects::Symbol(
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

bool Objects::Symbol::equalValue(const char* characters, Objects::SymbolType symbolType, unsigned short parameterCount) {
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