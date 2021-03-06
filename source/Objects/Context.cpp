#include "../Object_Layout/ObjectMap.hpp"
#include "../Object_Layout/MethodMap.hpp"


#include "ByteArray.hpp"
#include "ObjectArray.hpp"

#include "Context.hpp"



Objects::Context::Context(Object_Layout::ObjectMap* objectMap, Context* previous, Objects::SlotObject* reflectee) : Objects::SlotObject(objectMap) {
	this->_bytecodeIndex = 0;
	this->_previous = previous;
	this->_reflectee = reflectee;

	this->_objectType = Objects::ObjectType::Context;
};



Objects::Context* Objects::Context::clone(Memory::MemoryAllocator* allocator) {
	// Clonning of context is little different
	// Previous object of clonne is not same as previous context of clonned context
	// Instead , we will use clonned object(this) as previous context of clonned context - we need save integrity of context stack
	// Reflectee will be cloned - reflectee is just activation of method , we want 1 context = 1 method.
	Objects::Context* clonnedContext = new(allocator) Objects::Context(
		this->getObjectMap(),
		this,
		this->_reflectee->clone(allocator)
	);

	clonnedContext->_bytecodeIndex = this->_bytecodeIndex;
	return clonnedContext;
}


Objects::SlotObject* Objects::Context::getLiteral(unsigned short index) {
	return this->_reflectee->getLiterals()->at(index);
}
char Objects::Context::getBytecode() {
	return this->_reflectee->getBytecode()->at(this->_bytecodeIndex); 
};

void Objects::Context::incIndex() {
	this->_bytecodeIndex++;
}
void Objects::Context::setIndex(unsigned short newIndex) {
	this->_bytecodeIndex = newIndex;
}
char Objects::Context::getIndex() {
	return this->_bytecodeIndex;
}
bool Objects::Context::finished() {
	return (this->_bytecodeIndex) >= this->_reflectee->getBytecode()->getArrayLength(); 
}