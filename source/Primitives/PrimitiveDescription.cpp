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

Primitives::PrimitiveDescription::PrimitiveDescription(const char* _primitiveName, unsigned short _parameterCount, Objects::Object* (*_getRoutine())(Objects::Object**)) {
	this->_primitiveName = _primitiveName;
	this->_parameterCount = _parameterCount;

	this->calculateHash();

	this->_routine = _routine;
}

bool Primitives::PrimitiveDescription::equalName(Objects::Symbol* comparedName) {
	return comparedName->equalValue((char*)this->_primitiveName, Objects::SymbolType::AlphaNumerical, this->_parameterCount);
}