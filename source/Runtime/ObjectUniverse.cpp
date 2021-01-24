#include "../Memory/MemoryAllocator.hpp"

#include "../Object_Layout/ObjectMap.hpp"
#include "../Object_Layout/MethodMap.hpp"
#include "../Object_Layout/SlotDescription.hpp"

#include "../Objects/Assignment.hpp"
#include "../Objects/ByteArray.hpp"
#include "../Objects/Code.hpp"
#include "../Objects/Context.hpp"
#include "../Objects/Object.hpp"
#include "../Objects/ObjectArray.hpp"
#include "../Objects/ObjectFactory.hpp"
#include "../Objects/Process.hpp"
#include "../Objects/SmallInt.hpp"
#include "../Objects/String.hpp"
#include "../Objects/Symbol.hpp"
#include "../Objects/SymbolType.hpp" 

#include "ObjectUniverse.hpp"


Runtime::ObjectUniverse::ObjectUniverse(Memory::MemoryAllocator* basicAllocator, Memory::MemoryAllocator* tenuredAllocator, Memory::MemoryAllocator* pernamentAllocator) {
	this->_basicAllocator		= basicAllocator;
	this->_tenuredAllocator		= tenuredAllocator;
	this->_pernamentAllocator	= pernamentAllocator;
}


Objects::Object* Runtime::ObjectUniverse::createObject(unsigned short slotCount) {
	Object_Layout::ObjectMap* newMap = this->createObjectMap(slotCount);

	return newMap->constructObject(this->_basicAllocator);
}

Objects::Object* Runtime::ObjectUniverse::createObjectWithSlots(unsigned short slotCount, Object_Layout::SlotDescription descriptions[]) {
	Object_Layout::ObjectMap*	newMap = nullptr;
	Objects::Object*			newObject = nullptr;;
	if (slotCount == 1 && descriptions[0].isParent() && descriptions[0].getName()->equalValue("parent", Objects::SymbolType::AlphaNumerical, 0)) {
		return this->_parentMap->constructObject(this->_basicAllocator);
	}
	
	
	newMap = this->createObjectMap(slotCount);
	for (unsigned i = 0; i < slotCount; i++) {
		newMap->setDescription(i, descriptions[i]);
	}

	return newMap->constructObject(this->_basicAllocator);
}

Objects::Object* Runtime::ObjectUniverse::createObjectWithValues(unsigned short slotCount, Object_Layout::SlotDescription description[], Objects::Object* values[]) {
	Objects::Object* newObject = this->createObjectWithSlots(slotCount, description);
	
	for (unsigned i = 0; i < slotCount; i++) {
		newObject->setValue(i, values[i]);
	}

	return newObject;
}

Object_Layout::ObjectMap* Runtime::ObjectUniverse::createObjectMap(unsigned short slotCount) {
	if (slotCount == 0) {
		return this->_emptyMap;
	}	
	return Object_Layout::ObjectMap::create(this->_basicAllocator, slotCount);
}
