#include "../Memory/MemoryAllocator.hpp"

#include "../Object_Layout/ObjectMap.hpp"
#include "../Object_Layout/SlotDescription.hpp"
#include "../Object_Layout/SlotType.hpp"

#include "../Objects/Object.hpp"
#include "../Objects/ObjectFactory.hpp"
#include "../Objects/Symbol.hpp"

#include "ObjectWorld.hpp"


Runtime::ObjectWorld::ObjectWorld(Objects::ObjectFactory* objectFactory) {
	// initialize object world
	Object_Layout::ObjectMap* lobbyMap = objectFactory->createObjectMap(3);
	lobbyMap->setDescription(0, Object_Layout::SlotDescription(
		objectFactory->createSymbol("Lobby", Objects::SymbolType::AlphaNumerical, 0),
		Object_Layout::SlotType::NormalSlot
	));
	lobbyMap->setDescription(1, Object_Layout::SlotDescription(
		objectFactory->createSymbol("globals", Objects::SymbolType::AlphaNumerical, 0),
		Object_Layout::SlotType::ParentSlot 
	));
	lobbyMap->setDescription(2, Object_Layout::SlotDescription(
		objectFactory->createSymbol("traits", Objects::SymbolType::AlphaNumerical, 0),
		Object_Layout::SlotType::NormalSlot
	));


	this->lobbyObject = lobbyMap->constructObject(objectFactory->getAllocator());
	this->lobbyObject->setValue(0, this->lobbyObject); // slot Lobby is pointing to object Lobby


	Object_Layout::ObjectMap* globalsMap = objectFactory->createObjectMap(8);
	Object_Layout::ObjectMap* traitsMap = objectFactory->createObjectMap(7);

	// initialize important objects
	Object_Layout::ObjectMap* parentMap = objectFactory->createObjectMap(1);
	parentMap->setDescription(0, Object_Layout::SlotDescription(
		objectFactory->createSymbol("parent", Objects::SymbolType::AlphaNumerical, 0),
		Object_Layout::SlotType::ParentSlot
	));

	this->trueObject =		parentMap->constructObject(objectFactory->getAllocator());
	this->falseObject =		parentMap->constructObject(objectFactory->getAllocator());
	this->undefinedObject = parentMap->constructObject(objectFactory->getAllocator());
	
	
	// initialize prototypes


}