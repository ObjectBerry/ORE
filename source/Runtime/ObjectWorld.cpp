#include "../Memory/MemoryAllocator.hpp"

#include "../Object_Layout/ObjectMap.hpp"
#include "../Object_Layout/SlotDescription.hpp"
#include "../Object_Layout/SlotType.hpp"

#include "../Objects/Object.hpp"
#include "../Objects/ObjectArray.hpp"
#include "../Objects/ObjectFactory.hpp"
#include "../Objects/Symbol.hpp"

#include "ObjectWorld.hpp"


Runtime::ObjectWorld::ObjectWorld(Objects::ObjectFactory* objectFactory) {
	this->_objectFactory = objectFactory;
	// initialize object world
	const char* lobbyNames[] = { "Lobby", "globals", "traits", "bootstrap" };
	
	this->_lobbyObject = this->_objectFactory->createObjectMap(4)->constructObject(this->_objectFactory->getAllocator());
	this->setSlotNames(this->_lobbyObject->getObjectMap(), 4, lobbyNames);

	unsigned short prototypeCount = 2;
	this->_globalsObject = this->_objectFactory->createObjectMap(prototypeCount + 3)->constructObject(this->_objectFactory->getAllocator());
	this->_traitsObject  = this->_objectFactory->createObjectMap(prototypeCount + 2)->constructObject(this->_objectFactory->getAllocator());

	this->_lobbyObject->setValue(0, this->_lobbyObject);
	this->_lobbyObject->setValue(1, this->_globalsObject);
	this->_lobbyObject->setValue(2, this->_traitsObject);
	
	// initialize prototypes
	this->createFullPrototype("ByteArray", this->_objectFactory->createByteArray(1));
	this->createFullPrototype("ObjectArray", this->_objectFactory->createObjectArray(1));



	// initialize important objects 
	this->_trueObject		= this->_objectFactory->createObjectMap(1)->constructObject(this->_objectFactory->getAllocator());
	this->_falseObject		= this->_trueObject->clone(this->_objectFactory->getAllocator());
	this->_undefinedObject	= this->_trueObject->clone(this->_objectFactory->getAllocator());

	
}

void Runtime::ObjectWorld::setSlotNames(Object_Layout::ObjectMap* map, unsigned short nameCount, const char* names[]) {
	if (map->getSlotCount() != nameCount)
		return;

	for (unsigned i = 0; i < nameCount; i++) {
		map->setDescription(i, Object_Layout::SlotDescription(
			this->_objectFactory->createSymbol(names[i], Objects::SymbolType::AlphaNumerical, 0),
			Object_Layout::SlotType::NormalSlot
		));
	}
}

void Runtime::ObjectWorld::createFullPrototype(const char* name, Objects::Object* prototype) {
	Objects::Symbol* slotName = this->_objectFactory->createSymbol(name, Objects::SymbolType::AlphaNumerical, 0);


	Object_Layout::SlotDescription* slotDesc;
	Object_Layout::SlotDescription insertedSlot = Object_Layout::SlotDescription( slotName, Object_Layout::SlotType::NormalSlot);
	
	for (unsigned i = 0; i < this->_globalsObject->getSlotCount(); i++) {
		slotDesc = this->_globalsObject->getObjectMap()->getDescription(i);
		if (not slotDesc->isValid()) {
			this->_globalsObject->getObjectMap()->setDescription(i, insertedSlot);
			this->_globalsObject->setValue(i, prototype);
			return;
		}
	}

	Objects::Object* trait = this->_objectFactory->createObjectMap(0)->constructObject(this->_objectFactory->getAllocator());

	prototype->setValue(0, trait);

	for (unsigned i = 0; i < this->_traitsObject->getSlotCount(); i++) {
		slotDesc = this->_traitsObject->getObjectMap()->getDescription(i);
		if (not slotDesc->isValid()) {
			this->_traitsObject->getObjectMap()->setDescription(i, insertedSlot);
			this->_traitsObject->setValue(i, trait);
			return;
		}
	}
}