#include "../Memory/MemoryAllocator.hpp"

#include "../Object_Layout/ObjectMap.hpp"
#include "../Object_Layout/ExecutableMap.hpp"

#include "../Objects/ObjectFactory.hpp"
#include "../Objects/ObjectArray.hpp"
#include "../Objects/SmallInt.hpp"
#include "../Objects/Symbol.hpp"
#include "../Objects/SymbolType.hpp"

#include "ByteTranslator.hpp"

Compiler::ByteTranslator::ByteTranslator(Objects::ObjectFactory* objectFactory, char* bytes, unsigned short length) {
	this->_objectFactory	= objectFactory;
	this->_bytes			= bytes;
	this->_index			= 0;
	this->_lenght			= length;
}

bool Compiler::ByteTranslator::isLimit(unsigned short requestedBytes) {
	return (this->_index + requestedBytes) >= this->_lenght;
}
int Compiler::ByteTranslator::translateNumber(unsigned char numberBytes){
	int number = 0;
	switch (numberBytes) {
	case 4:
		number += this->_bytes[this->_index++];
		number <<= 8;
	case 3:
		number += this->_bytes[this->_index++];
		number <<= 8;
	case 2:
		number += this->_bytes[this->_index++];
		number <<= 8;
	case 1:
		number += this->_bytes[this->_index++];
	}

	return number;
}
	
Objects::Object* Compiler::ByteTranslator::translateLiteral() {
	if (this->isLimit(2)) {
		throw 1;
	}

	switch (this->_bytes[this->_index++]) {
	case 0x00:
		this->_index++;
		return nullptr;
	case 0x01:
		return this->translateSmallInt();
	case 0x02:
		// float
	case 0x04:
		return this->translateSymbol();
	case 0x0B:
		return this->translateObject();
	case 0x0C:


	default:
		this->_index--;
		return nullptr;
	}
}

Objects::SmallInt* Compiler::ByteTranslator::translateSmallInt() {
	signed int value = 0;
	if (this->isLimit(4)) 
		throw 1;
	
	value = this->translateNumber(4);

	return this->_objectFactory->createSmallInt(value);
}

Objects::Symbol* Compiler::ByteTranslator::translateSymbol() {
	if (this->isLimit(4)) 
		throw 1;
	

	Objects::SymbolType symbolType = static_cast<Objects::SymbolType>(this->_bytes[this->_index++]);
	unsigned short parameterCount = static_cast<unsigned short>(this->translateNumber(2));

	unsigned short localIndex = this->_index;
	unsigned short stringLength = 0;

	while (localIndex < this->_lenght && this->_bytes[localIndex] != '\0') {
		stringLength++;
		localIndex++;
	}
	if (this->_lenght == localIndex)
		return nullptr;

	char* characters = this->_objectFactory->getAllocator()->allocateBytes(stringLength + 1);
	for (unsigned i = 0; i < stringLength + 1; i++) {
		characters[i] = this->_bytes[this->_index++];
	}

	return this->_objectFactory->createSymbol(characters, symbolType, parameterCount);
}

Compiler::CodeDescription Compiler::ByteTranslator::translateCode() {
	if (this->isLimit(5))
		throw 1;

	unsigned short literalsCount	= static_cast<unsigned short>(this->translateNumber(2));
	unsigned short bytecodesCount	= static_cast<unsigned short>(this->translateNumber(2));
	

	Objects::ObjectArray* literals = nullptr;
	if (literalsCount > 0) {
		literals = this->_objectFactory->createObjectArray(literalsCount);
		
		for (unsigned i = 0; i < literalsCount; i++) {
			literals->atPut(i, this->translateLiteral());
		}
	}

	if(this->isLimit(bytecodesCount))
		throw 1;

	// move bytes into byte array
	Objects::ByteArray* bytecodes = this->_objectFactory->createByteArray(bytecodesCount);
	for (unsigned i = 0; i < bytecodesCount; i++) {
		bytecodes->atPut(i, this->_bytes[this->_index]);
		this->_index++;
	}

	return Compiler::CodeDescription{ literals, bytecodes };

}

Objects::Object* Compiler::ByteTranslator::translateObject() {
	if (this->isLimit(3))
		throw 1;

	unsigned short slotCount = this->translateNumber(2);
	Object_Layout::ObjectMap* objMap = this->_objectFactory->createObjectMap(slotCount);
}

Objects::Object* Compiler::ByteTranslator::translateExecutable() {
	if (this->isLimit(5))
		throw 1;

	unsigned short slotCount = this->translateNumber(2);
}
