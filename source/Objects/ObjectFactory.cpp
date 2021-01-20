#include "../Memory/MemoryAllocator.hpp"

#include "../Object_Layout/ExecutableMap.hpp"
#include "../Object_Layout/ObjectMap.hpp"
#include "../Object_Layout/SlotDescription.hpp"
#include "../Object_Layout/SlotType.hpp"

#include "Assignment.hpp"
#include "ByteArray.hpp"
#include "Code.hpp"
#include "Context.hpp"
#include "Object.hpp"
#include "ObjectArray.hpp"
#include "ObjectFactory.hpp"
#include "Process.hpp"
#include "SmallInt.hpp"
#include "Symbol.hpp"
#include "SymbolType.hpp"


Objects::ObjectFactory::ObjectFactory(Memory::MemoryAllocator* _normalAllocator, Memory::MemoryAllocator* _pernamentAllocator) {
	this->_normalAllocator		= _normalAllocator;
	this->_pernamentAllocator	= _pernamentAllocator;
	this->initializeMaps();
}
void Objects::ObjectFactory::initializeMaps() {
	//first we must initialize symbol map because symbol will be alredy used in cached object maps
	this->_symbolMap = Object_Layout::ObjectMap::create(this->_pernamentAllocator, 1);
	Objects::Symbol* parentSymbol = this->createSymbol("parent", Objects::SymbolType::AlphaNumerical, 0);

	this->_symbolMap->setDescription(0, Object_Layout::SlotDescription(parentSymbol, Object_Layout::SlotType::ParentSlot));

	this->_assignmentMap	= this->_symbolMap->clone(this->_pernamentAllocator);
	this->_byteArrayMap		= this->_symbolMap->clone(this->_pernamentAllocator);
	this->_codeMap			= this->_symbolMap->clone(this->_pernamentAllocator);
	this->_contextMap		= this->_symbolMap->clone(this->_pernamentAllocator);
	this->_objectArrayMap	= this->_symbolMap->clone(this->_pernamentAllocator);
	this->_processMap		= this->_symbolMap->clone(this->_pernamentAllocator);
	this->_smallIntMap		= this->_symbolMap->clone(this->_pernamentAllocator);
}

Objects::Assignment* Objects::ObjectFactory::createAssignment(Objects::Symbol* assignedSlot) {
	return Objects::Assignment::create(this->_normalAllocator, this->_assignmentMap, assignedSlot);
}
Objects::ByteArray* Objects::ObjectFactory::createByteArray(unsigned short arrayLength) {
	return Objects::ByteArray::create(this->_normalAllocator, this->_byteArrayMap, arrayLength);
}
Objects::Code* Objects::ObjectFactory::createCode(Objects::ByteArray* bytecodes, Objects::ObjectArray* literals) {
	return Objects::Code::create(this->_normalAllocator, this->_codeMap, bytecodes, literals);
}
Objects::Context* Objects::ObjectFactory::createContext(Objects::Context* previous, Objects::Object* reflectee) {
	return Objects::Context::create(this->_normalAllocator, this->_contextMap, previous, reflectee);
}
Objects::ObjectArray* Objects::ObjectFactory::createObjectArray(unsigned short arrayLength) {
	return Objects::ObjectArray::create(this->_normalAllocator, this->_objectArrayMap, arrayLength);
};
Objects::Process* Objects::ObjectFactory::createProcess(unsigned short stackLength) {
	return Objects::Process::create(
		this->_normalAllocator,
		this->_processMap,
		this->createObjectArray(stackLength)
	);
}
Objects::SmallInt* Objects::ObjectFactory::createSmallInt(signed int value) {
	return Objects::SmallInt::create(this->_normalAllocator, this->_smallIntMap, value);
}
Objects::Symbol* Objects::ObjectFactory::createSymbol(const char* characters, Objects::SymbolType symbolType, unsigned short parameterCount) {
	return Objects::Symbol::create(
		this->_normalAllocator,
		this->_symbolMap,
		const_cast<char*>(characters),
		symbolType,
		parameterCount
	);
}


Object_Layout::ObjectMap* Objects::ObjectFactory::createObjectMap(unsigned short  slotCount) {
	return Object_Layout::ObjectMap::create(this->_normalAllocator, slotCount);
}
Object_Layout::ExecutableMap* Objects::ObjectFactory::createExecutableMap(unsigned short slotCount, Objects::ByteArray* bytecodes, Objects::ObjectArray* literals, Object_Layout::ScopeType scopeType, Object_Layout::ReturnType returnType) {
	return Object_Layout::ExecutableMap::create(this->_normalAllocator, slotCount, bytecodes, literals, scopeType, returnType);
}