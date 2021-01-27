#include "../Memory/MemoryAllocator.hpp"

#include "../Object_Layout/ObjectMap.hpp"
#include "../Object_Layout/MethodMap.hpp"
#include "../Object_Layout/SlotType.hpp"
#include "../Object_Layout/SlotDescription.hpp"


#include "../Objects/Assignment.hpp"
#include "../Objects/ObjectArray.hpp"
#include "../Objects/SmallInt.hpp"
#include "../Objects/String.hpp"
#include "../Objects/Symbol.hpp"
#include "../Objects/SymbolType.hpp"

#include "../Runtime/ObjectUniverse.hpp"

#include "TranslatorError.hpp"
#include "LiteralType.hpp"
#include "ByteTranslator.hpp"

Compiler::ByteTranslator::ByteTranslator(Runtime::ObjectUniverse* objectUniverse, char* bytes, unsigned short length) {
	this->_objectUniverse	= objectUniverse;
	this->_bytes			= bytes;
	this->_index			= 0;
	this->_lenght			= length;
}

void Compiler::ByteTranslator::isLimit(unsigned short requestedBytes) {
	if ((this->_index + requestedBytes) > this->_lenght) {
		throw Compiler::TranslatorError::NotEnoughBytes;
	}
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
	this->isLimit(2);

	switch (static_cast<Compiler::LiteralType>( this->_bytes[this->_index++])) {
	case Compiler::LiteralType::Undefined:
		return nullptr;
	
	case Compiler::LiteralType::AssignmentLit:
		return this->translateAssignment();

	case Compiler::LiteralType::SmallIntLit:
		return this->translateSmallInt();

	case Compiler::LiteralType::FloatLit:
		// TODD: Implement float translation
	
	case Compiler::LiteralType::StringLit:
		return this->translateString();

	case Compiler::LiteralType::SymbolLit:
		return this->translateSymbol();

	case Compiler::LiteralType::ObjectLit:
		return this->translateObject();

	case Compiler::LiteralType::MethodLit:
		// TODO: Implement method translation

	case Compiler::LiteralType::EvalLit:
		// TODO: Implement evaluation literal (literal that is decised at runtime (this will be hard :( )
		
	default:
		this->_index--;
		throw Compiler::TranslatorError::InvalidLiteralType;
	}
}
Objects::Assignment* Compiler::ByteTranslator::translateAssignment() {
	Objects::Symbol* assignedSymbol = this->translateSymbol();

	return this->_objectUniverse->createAssignment(assignedSymbol);
}

Objects::SmallInt* Compiler::ByteTranslator::translateSmallInt() {
	signed int value = 0;
	this->isLimit(4);
		
	
	value = this->translateNumber(4);

	return this->_objectUniverse->createSmallInt(value);
}

Objects::String* Compiler::ByteTranslator::translateString() {
	unsigned short localIndex = this->_index;
	unsigned short stringLength = 0;

	while (localIndex < this->_lenght && this->_bytes[localIndex] != '\0') {
		stringLength++;
		localIndex++;
	}
	if (this->_lenght == localIndex)
		throw Compiler::TranslatorError::NotEnoughBytes;

	char* characters = this->_objectUniverse->getAllocator()->allocateBytes(stringLength + 1);
	for (unsigned i = 0; i < stringLength + 1; i++) {
		characters[i] = this->_bytes[this->_index++];
	}

	return this->_objectUniverse->createString(characters); 
}

Objects::Symbol* Compiler::ByteTranslator::translateSymbol() {
	this->isLimit(4);
	
	

	Objects::SymbolType symbolType = static_cast<Objects::SymbolType>( static_cast<unsigned char>( this->_bytes[this->_index++] ) );
	unsigned short parameterCount = static_cast<unsigned short>(this->translateNumber(2));

	unsigned short localIndex = this->_index;
	unsigned short stringLength = 0;

	while (localIndex < this->_lenght && this->_bytes[localIndex] != '\0') {
		stringLength++;
		localIndex++;
	}
	if (this->_lenght == localIndex)
		throw Compiler::TranslatorError::NotEnoughBytes;

	char* characters = this->_objectUniverse->getAllocator()->allocateBytes(stringLength + 1);
	for (unsigned i = 0; i < stringLength + 1; i++) {
		characters[i] = this->_bytes[this->_index++];
	}

	return this->_objectUniverse->createSymbol(characters, symbolType, parameterCount);
}

Compiler::CodeDescription Compiler::ByteTranslator::translateCode() {
	this->isLimit(5);
		

	unsigned short literalsCount	= static_cast<unsigned short>(this->translateNumber(2));
	unsigned short bytecodesCount	= static_cast<unsigned short>(this->translateNumber(2));
	

	Objects::ObjectArray* literals = nullptr;
	if (literalsCount > 0) {
		literals = this->_objectUniverse->createObjectArray(literalsCount);
		
		for (unsigned i = 0; i < literalsCount; i++) {
			literals->atPut(i, this->translateLiteral());
		}
	}

	this->isLimit(bytecodesCount);


	// move bytes into byte array
	Objects::ByteArray* bytecodes = this->_objectUniverse->createByteArray(bytecodesCount);
	for (unsigned i = 0; i < bytecodesCount; i++) {
		bytecodes->atPut(i, this->_bytes[this->_index]);
		this->_index++;
	}

	return Compiler::CodeDescription{ literals, bytecodes };

}

Objects::Object* Compiler::ByteTranslator::translateObject() {
	this->isLimit(3);

	unsigned short slotCount = this->translateNumber(2);

	Object_Layout::ObjectMap* objectMap = this->_objectUniverse->createObjectMap(slotCount);
	Objects::Object* resultObject		= objectMap->constructObject(this->_objectUniverse->getAllocator());

	if (slotCount == 0) {
		return resultObject;
	}

	Objects::Symbol*		slotName = nullptr;
	Object_Layout::SlotType slotType = Object_Layout::SlotType::UnititalizedSlot;
	Objects::Object*		slotData = nullptr;

	for (unsigned i = 0; i < slotCount; i++) {
		slotName = this->translateSymbol();
		// TODO: Fix this hack
		unsigned int x = static_cast<unsigned int>(this->_bytes[this->_index++]);
		x <<= 24; x >>= 24;
		slotType = static_cast<Object_Layout::SlotType>(x);

		if (slotType == Object_Layout::SlotType::NormalParameter or slotType == Object_Layout::SlotType::ParentParameter)
			throw 3; // add new exception for this

		slotData = this->translateLiteral();

		objectMap->setDescription(i, Object_Layout::SlotDescription(
			slotName,
			slotType
		));
		resultObject->setValue(i, slotData);
	}

	return resultObject;
}

Objects::Object* Compiler::ByteTranslator::translateMethod() {
	this->isLimit(3);
	unsigned short slotCount = this->translateNumber(2);

	Object_Layout::MethodMap* methodMap = this->_objectUniverse->createMethodMap(slotCount);
	
	Objects::Object* resultObject = methodMap->constructObject(this->_objectUniverse->getAllocator());

	if (slotCount > 0) {
		Objects::Symbol* slotName = nullptr;
		Object_Layout::SlotType slotType = Object_Layout::SlotType::UnititalizedSlot;
		Objects::Object* slotData = nullptr;

		for (unsigned i = 1; i < slotCount + 1; i++) {
			slotName = this->translateSymbol();
			// TODO: Fix this hack
			unsigned int x = static_cast<unsigned int>(this->_bytes[this->_index++]);
			x <<= 24; x >>= 24;
			slotType = static_cast<Object_Layout::SlotType>(x);
			slotData = this->translateLiteral();

			methodMap->setDescription(i, Object_Layout::SlotDescription(
				slotName,
				slotType
			));
			resultObject->setValue(i, slotData);
		}
	}

	this->isLimit(3);
	
	Object_Layout::ScopeType	scopeType = static_cast<Object_Layout::ScopeType>(this->_bytes[this->_index++]);
	Object_Layout::ReturnType	returnType = static_cast<Object_Layout::ReturnType>(this->_bytes[this->_index++]);
	CodeDescription codeDesc = this->translateCode();

	methodMap->setCodeDescription(
		codeDesc._bytecodes,
		codeDesc._literals,
		scopeType,
		returnType
	);

	return resultObject;
}



