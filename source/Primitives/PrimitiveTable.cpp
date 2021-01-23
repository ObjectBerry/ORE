#include "../Objects/Symbol.hpp"

#include "PrimitiveDescription.hpp"

#include "PrimitiveTable.hpp"

Primitives::PrimitiveTable::PrimitiveTable(unsigned short length) {
	this->_length	= length;
	this->_count	= 0;
	this->_storage	= new Primitives::PrimitiveDescription[this->_length];
}


unsigned int Primitives::PrimitiveTable::hashSymbol(const char* characters, unsigned short length, Objects::SymbolType symbolType, unsigned short parameterCount) {
	unsigned int hash = 2166136261u;
	for (int i = 0; i < length; i++) {
		hash ^= characters[i];
		hash *= 16777619;
	}
	hash ^= static_cast<char>(symbolType);
	hash *= 16777619;
	hash ^= parameterCount;
	hash *= 16777619;

	return hash;
}



void Primitives::PrimitiveTable::addPrimitive(Primitives::PrimitiveDescription primitiveDescription) {
	unsigned int hash = this->hashSymbol(
		primitiveDescription.getName(),
		primitiveDescription.getNameLength(),
		Objects::SymbolType::AlphaNumerical,
		primitiveDescription.getParameterCount()
	);

	unsigned int primitiveIndex = hash % this->_length;
	Primitives::PrimitiveDescription* activeDesc = nullptr;
	while (true) {
		activeDesc = &(this->_storage[primitiveIndex]);

		if (activeDesc == nullptr) {
			this->_storage[primitiveIndex] = primitiveDescription;
			this->_count++;
			return;
		}
		primitiveIndex = (primitiveIndex + 1) % this->_length;
	}
}

Primitives::PrimitiveDescription* Primitives::PrimitiveTable::getPrimitive(Objects::Symbol* symbol) {
	unsigned int hash = this->hashSymbol(
		symbol->getArrayStorage(),
		symbol->getArrayLength(),
		symbol->getSymbolType(),
		symbol->getSymbolParameters() 
	);
	unsigned int primitiveIndex = hash % this->_length;
	Primitives::PrimitiveDescription* activeDesc = nullptr;
	while (true) {
		activeDesc = &(this->_storage[primitiveIndex]);

		if (activeDesc == nullptr) {	
			return nullptr;
		}
		if (activeDesc->equalValue(symbol->getArrayStorage(), symbol->getArrayLength())) {
			return activeDesc;
		}
		primitiveIndex = (primitiveIndex + 1) % this->_length;
	}
}