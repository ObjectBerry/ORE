#include "../Memory/MemoryAllocator.hpp"

#include "../Object_Layout/ObjectMap.hpp"
#include "../Object_Layout/MethodMap.hpp"
#include "../Object_Layout/SlotDescription.hpp"
#include "../Object_Layout/SlotType.hpp"

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
	this->_basicAllocator		= tenuredAllocator; // this is little hack that will enforce usage of tenured memory during initialization of object world
	this->_tenuredAllocator		= tenuredAllocator;
	this->_pernamentAllocator	= pernamentAllocator;

	this->initializeTraits(); 
	this->initializeMaps();

	this->_basicAllocator		= basicAllocator;
}

void Runtime::ObjectUniverse::genesis() {
	Memory::MemoryAllocator* alloc = this->_basicAllocator;
	this->_basicAllocator = this->_tenuredAllocator;

	this->initializeSystemObjects();
	this->initializeStructure();

	this->_basicAllocator = alloc;
}



void Runtime::ObjectUniverse::initializeMaps() {
	this->_parentMap = this->createObjectMap(1);
	this->_parentMap->setDescription(0, Object_Layout::SlotDescription(
		this->createSymbol("parent", Objects::SymbolType::AlphaNumerical, 0),
		Object_Layout::SlotType::ParentSlot
	));
}
void Runtime::ObjectUniverse::initializeTraits() {
	this->_emptyMap = Object_Layout::ObjectMap::create(this->_pernamentAllocator, 0);

#define createObj this->_emptyMap->constructObject(this->_tenuredAllocator)

	this->_assignmentTrait	= createObj;
	this->_byteArrayTrait	= createObj;
	this->_contextTrait		= createObj;
	this->_objectArrayTrait = createObj; 
	this->_processTrait		= createObj;
	this->_smallIntTrait	= createObj; 
	this->_stringTrait		= createObj;
	this->_symbolTrait		= createObj;
	
#undef createObj
}

void Runtime::ObjectUniverse::initializeSystemObjects() {
	this->_trueObject		= this->_parentMap->constructObject(this->_tenuredAllocator);
	this->_falseObject		= this->_parentMap->constructObject(this->_tenuredAllocator);
	this->_undefinedObject	= this->_parentMap->constructObject(this->_tenuredAllocator);
}

void Runtime::ObjectUniverse::initializeStructure() {
#define alphaNumSymbol(chr) this->createSymbol(chr, Objects::SymbolType::AlphaNumerical, 0)

	// Lobby initialization
	Object_Layout::SlotDescription lobbyDescriptions[4] = {
		Object_Layout::SlotDescription(alphaNumSymbol("Lobby"),		Object_Layout::SlotType::NormalSlot),
		Object_Layout::SlotDescription(alphaNumSymbol("globals"),	Object_Layout::SlotType::ParentSlot),
		Object_Layout::SlotDescription(alphaNumSymbol("traits"),	Object_Layout::SlotType::NormalSlot),
		Object_Layout::SlotDescription(alphaNumSymbol("bootstrap"), Object_Layout::SlotType::NormalSlot),
	};
	this->_lobbyObject = this->createObjectWithSlots(4, lobbyDescriptions);

	// Globals initialization
	Object_Layout::SlotDescription globalsDescription[5] = {
		Object_Layout::SlotDescription(alphaNumSymbol("ByteArray"),			Object_Layout::SlotType::NormalSlot),
		Object_Layout::SlotDescription(alphaNumSymbol("ObjectArray"),		Object_Layout::SlotType::NormalSlot),
		Object_Layout::SlotDescription(alphaNumSymbol("Undefined"),			Object_Layout::SlotType::NormalSlot),
		Object_Layout::SlotDescription(alphaNumSymbol("True"),				Object_Layout::SlotType::NormalSlot),
		Object_Layout::SlotDescription(alphaNumSymbol("False"),				Object_Layout::SlotType::NormalSlot),
	};
	Objects::Object* globalsValues[11] = {
		this->createByteArray(1),
		this->createObjectArray(1),
		this->_undefinedObject,
		this->_trueObject,
		this->_falseObject
	};
	this->_globalsObject = this->createObjectWithValues(5, globalsDescription, globalsValues);

	// Traits initialization
	Objects::Object* booleanTrait	= this->createObject(0);
	Objects::Object* undefinedTrait = this->createObject(0);

	Object_Layout::SlotDescription traitsDescriptions[10] = {
		Object_Layout::SlotDescription(alphaNumSymbol("Assignment"),		Object_Layout::SlotType::NormalSlot),
		Object_Layout::SlotDescription(alphaNumSymbol("ByteArray"),			Object_Layout::SlotType::NormalSlot),
		Object_Layout::SlotDescription(alphaNumSymbol("Context"),			Object_Layout::SlotType::NormalSlot),
		Object_Layout::SlotDescription(alphaNumSymbol("ObjectArray"),		Object_Layout::SlotType::NormalSlot),
		Object_Layout::SlotDescription(alphaNumSymbol("Process"),			Object_Layout::SlotType::NormalSlot),
		Object_Layout::SlotDescription(alphaNumSymbol("SmallInt"),			Object_Layout::SlotType::NormalSlot),
		Object_Layout::SlotDescription(alphaNumSymbol("String"),			Object_Layout::SlotType::NormalSlot),
		Object_Layout::SlotDescription(alphaNumSymbol("Symbol"),	 		Object_Layout::SlotType::NormalSlot),
		Object_Layout::SlotDescription(alphaNumSymbol("Undefined"),			Object_Layout::SlotType::NormalSlot),
		Object_Layout::SlotDescription(alphaNumSymbol("Boolean"),			Object_Layout::SlotType::NormalSlot),
	};
	Objects::Object* traitsValues[10] = {
		this->_assignmentTrait,
		this->_byteArrayTrait,
		this->_contextTrait,
		this->_objectArrayTrait,
		this->_processTrait,
		this->_smallIntTrait,
		this->_stringTrait,
		this->_symbolTrait,
		undefinedTrait,
		booleanTrait,  
	};
	this->_traitsObject = this->createObjectWithValues(10, traitsDescriptions, traitsValues);

	// add links between structure objects
	this->_lobbyObject->setValue(0, this->_lobbyObject); // lobby is "self-named object" - it contains slot that is pointing to itself
	this->_lobbyObject->setValue(1, this->_globalsObject);
	this->_lobbyObject->setValue(2, this->_traitsObject); 

	this->_trueObject->setValue(0, booleanTrait);
	this->_falseObject->setValue(0, booleanTrait);
	this->_undefinedObject->setValue(0, undefinedTrait); 

#undef alphaNumSymbol 
}

// Basic Object creation
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

// Method Object creation

// Specialized Object creation
#define CREATE_OBJ(ObjectName, parameters) Objects::##ObjectName* new##ObjectName = Objects::##ObjectName::create
#define SHARED_PARAM this->_basicAllocator, this->_parentMap
#define SET_TRAIT(Obj, Trait) Obj->setValue(0, Trait)

Objects::Assignment* Runtime::ObjectUniverse::createAssignment(Objects::Symbol* associatedSlot) {
	CREATE_OBJ(Assignment)(SHARED_PARAM, associatedSlot);
	SET_TRAIT(newAssignment, this->_assignmentTrait);

	return newAssignment;
}

Objects::ByteArray* Runtime::ObjectUniverse::createByteArray(unsigned short arrayLength) {
	CREATE_OBJ(ByteArray)(SHARED_PARAM, arrayLength);
	SET_TRAIT(newByteArray, this->_byteArrayTrait);

	return newByteArray; 
}

Objects::Context* Runtime::ObjectUniverse::createContext(Objects::Context* previous, Objects::Object* reflectee) {
	CREATE_OBJ(Context)(SHARED_PARAM, previous, reflectee);
	SET_TRAIT(newContext, this->_contextTrait);

	return newContext;
}

Objects::ObjectArray* Runtime::ObjectUniverse::createObjectArray(unsigned short arrayLength) {
	CREATE_OBJ(ObjectArray)(SHARED_PARAM, arrayLength);
	SET_TRAIT(newObjectArray, this->_objectArrayTrait);

	return newObjectArray;
}

Objects::Process* Runtime::ObjectUniverse::createProcess(unsigned short stackSize) {
	CREATE_OBJ(Process)(SHARED_PARAM, this->createObjectArray(stackSize));
	SET_TRAIT(newProcess, this->_processTrait);

	return newProcess;
}

Objects::SmallInt* Runtime::ObjectUniverse::createSmallInt(signed int value) {
	CREATE_OBJ(SmallInt)(SHARED_PARAM, value);
	SET_TRAIT(newSmallInt, this->_smallIntTrait);

	return newSmallInt;
}

Objects::String* Runtime::ObjectUniverse::createString(const char* characters) {
	CREATE_OBJ(String)(SHARED_PARAM, characters);
	SET_TRAIT(newString, this->_stringTrait); 

	return newString;
}

Objects::Symbol* Runtime::ObjectUniverse::createSymbol(const char* characters, Objects::SymbolType symbolType, unsigned short parameterCount) {
	CREATE_OBJ(Symbol)(SHARED_PARAM, (char*)characters, symbolType, parameterCount);
	SET_TRAIT(newSymbol, this->_symbolTrait);

	return newSymbol;
}

#undef CREATE_OBJ
#undef SHARED_PARAM
#undef SET_TRAIT