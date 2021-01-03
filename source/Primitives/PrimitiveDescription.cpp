#include "../Objects/Symbol.hpp"

#include "PrimitiveDescription.hpp"

void Primitives::PrimitiveDescription::calculateHash() {
	this->_hash = 2166136261u;
	unsigned int length = 0;
	while (this->_primitiveName[length] != '\0') {
		length++;
	}

	for (int i = 0; i < length; i++) {
		this->_hash ^= this->_primitiveName[length];
		this->_hash *= 16777619;
	}
	this->_hash ^= static_cast<char>(Objects::SymbolType::AlphaNumerical);
	this->_hash *= 16777619;

	this->_hash ^= this->_parameterCount;
	this->_hash *= 16777619;
}

unsigned int Primitives::PrimitiveDescription::hashCharacters(char* _primitiveName,unsigned short _length, unsigned short _parameterCount) {
	unsigned int hash = 2166136261u;
	for (int i = 0; i < _length; i++) {
		hash ^= _primitiveName[_length];
		hash *= 16777619;
	}
	hash ^= static_cast<char>(Objects::SymbolType::AlphaNumerical);
	hash *= 16777619;

	hash ^= _parameterCount;
	hash *= 16777619;

	return hash;
}



Primitives::PrimitiveDescription::PrimitiveDescription() {
	this->_primitiveName = nullptr;

	this->_routine = nullptr;
}
Primitives::PrimitiveDescription::PrimitiveDescription(const char* _primitiveName, unsigned short _parameterCount, Objects::Object* (*_getRoutine())(Objects::Object**)) {
	this->_primitiveName = _primitiveName;
	this->_parameterCount = _parameterCount;

	this->calculateHash();

	this->_routine = _routine;
}

bool Primitives::PrimitiveDescription::equalName(Objects::Symbol* comparedName) {
	return comparedName->equalValue((char*)this->_primitiveName, Objects::SymbolType::AlphaNumerical, this->_parameterCount);
}