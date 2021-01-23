#include "../Objects/Object.hpp"

#include "PrimitiveDescription.hpp"

Primitives::PrimitiveDescription::PrimitiveDescription() {
	this->_primitiveName = nullptr;
	this->_nameLength = 0;
	this->_parameterCount = 0;
	this->_routine = 0;
}

Primitives::PrimitiveDescription::PrimitiveDescription(const char* primitiveName, unsigned short parameterCount, Objects::Object* (*routine)(Runtime::DependencyContainer* dc, Objects::Object** parameters)) {
	this->_primitiveName = primitiveName;
	this->_parameterCount = parameterCount;
	this->_routine = routine;

	this->_nameLength = 0;
	while (this->_primitiveName[this->_nameLength] != '\0')
		this->_nameLength++;
	this->_nameLength++;
	
}

bool Primitives::PrimitiveDescription::equalValue(const char* name, unsigned short nameLength) {
	if (this->_nameLength != nameLength)
		return false;

	for (unsigned i = 0; i < this->_nameLength; i++) {
		if (this->_primitiveName[i] != name[i])
			return false;
	};

	return true;
}