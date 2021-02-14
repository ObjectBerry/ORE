#include "../Memory/MemoryAllocator.hpp"

#include "../Compiler/ByteTranslator.hpp"

#include "../Object_Layout/ObjectMap.hpp"
#include "../Object_Layout/MethodMap.hpp"
#include "../Object_Layout/SlotDescription.hpp"
#include "../Object_Layout/SlotType.hpp"

#include "../Objects/Assignment.hpp"
#include "../Objects/ByteArray.hpp"
#include "../Objects/Context.hpp"
#include "../Objects/Mirror.hpp"
#include "../Objects/SlotObject.hpp"
#include "../Objects/ObjectArray.hpp"
#include "../Objects/Process.hpp"
#include "../Objects/SmallInt.hpp"
#include "../Objects/String.hpp"
#include "../Objects/Symbol.hpp"
#include "../Objects/SymbolType.hpp" 

#include "Metaverse.hpp"
#include "ObjectUniverse.hpp"


Runtime::ObjectUniverse::ObjectUniverse(Memory::MemoryAllocator* basicAllocator, Memory::MemoryAllocator* tenuredAllocator, Memory::MemoryAllocator* pernamentAllocator) {
	this->_basicAllocator		= tenuredAllocator; // this is little hack that will enforce usage of tenured memory during initialization of object world
	this->_tenuredAllocator		= tenuredAllocator;
	this->_pernamentAllocator	= pernamentAllocator;

	this->initializeTraits(); 
	this->initializeMaps();

	this->_basicAllocator		= basicAllocator;
}
Runtime::ObjectUniverse::ObjectUniverse(Runtime::Metaverse* metaverse) : Runtime::ObjectUniverse(
	metaverse->getBasicAllocator(),
	metaverse->getTenuredAllocator(),
	metaverse->getPernamentAllocator()
){ }

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
	this->_emptyMap = new(this->_pernamentAllocator) Object_Layout::ObjectMap(0);

#define createObj this->_emptyMap->constructObject(this->_tenuredAllocator)

	this->_assignmentTrait	= createObj;
	this->_byteArrayTrait	= createObj;
	this->_contextTrait		= createObj;
	this->_mirrorTrait		= createObj;
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
	Objects::SlotObject* globalsValues[11] = {
		this->createByteArray(1),
		this->createObjectArray(1),
		this->_undefinedObject,
		this->_trueObject,
		this->_falseObject
	};
	this->_globalsObject = this->createObjectWithValues(5, globalsDescription, globalsValues);

	// Traits initialization
	Objects::SlotObject* booleanTrait	= this->createObject(0);
	Objects::SlotObject* undefinedTrait = this->createObject(0);

	Object_Layout::SlotDescription traitsDescriptions[11] = {
		Object_Layout::SlotDescription(alphaNumSymbol("Assignment"),		Object_Layout::SlotType::NormalSlot),
		Object_Layout::SlotDescription(alphaNumSymbol("ByteArray"),			Object_Layout::SlotType::NormalSlot),
		Object_Layout::SlotDescription(alphaNumSymbol("Context"),			Object_Layout::SlotType::NormalSlot),
		Object_Layout::SlotDescription(alphaNumSymbol("Mirror"),			Object_Layout::SlotType::NormalSlot),
		Object_Layout::SlotDescription(alphaNumSymbol("ObjectArray"),		Object_Layout::SlotType::NormalSlot),
		Object_Layout::SlotDescription(alphaNumSymbol("Process"),			Object_Layout::SlotType::NormalSlot),
		Object_Layout::SlotDescription(alphaNumSymbol("SmallInt"),			Object_Layout::SlotType::NormalSlot),
		Object_Layout::SlotDescription(alphaNumSymbol("String"),			Object_Layout::SlotType::NormalSlot),
		Object_Layout::SlotDescription(alphaNumSymbol("Symbol"),	 		Object_Layout::SlotType::NormalSlot),
		Object_Layout::SlotDescription(alphaNumSymbol("Undefined"),			Object_Layout::SlotType::NormalSlot),
		Object_Layout::SlotDescription(alphaNumSymbol("Boolean"),			Object_Layout::SlotType::NormalSlot),
	};
	Objects::SlotObject* traitsValues[11] = {
		this->_assignmentTrait,
		this->_byteArrayTrait,
		this->_contextTrait,
		this->_mirrorTrait,
		this->_objectArrayTrait,
		this->_processTrait,
		this->_smallIntTrait,
		this->_stringTrait,
		this->_symbolTrait,
		undefinedTrait,
		booleanTrait,  
	};
	this->_traitsObject = this->createObjectWithValues(11, traitsDescriptions, traitsValues);

	// add links between structure objects
	this->_lobbyObject->setValue(0, this->_lobbyObject); // lobby is "self-named object" - it contains slot that is pointing to itself
	this->_lobbyObject->setValue(1, this->_globalsObject);
	this->_lobbyObject->setValue(2, this->_traitsObject); 

	this->_trueObject->setValue(0, booleanTrait);
	this->_falseObject->setValue(0, booleanTrait);
	this->_undefinedObject->setValue(0, undefinedTrait); 

#undef alphaNumSymbol 
}

void Runtime::ObjectUniverse::initializeBootstrap(Compiler::CodeDescription codeDescription, Objects::ObjectArray* commandLineArguments) {
	

	Object_Layout::SlotDescription descriptions[] = {
		Object_Layout::SlotDescription(
			this->createSymbol("lineParameters", Objects::SymbolType::AlphaNumerical, 0),
			Object_Layout::SlotType::NormalSlot
		)
	};

	this->_bootstrapMethod = this->createMethodWithSlots(1, descriptions);
	reinterpret_cast<Object_Layout::MethodMap*>(this->_bootstrapMethod->getObjectMap())->setCodeDescription(
		codeDescription._bytecodes,
		codeDescription._literals,
		Object_Layout::ScopeType::Lexical,
		Object_Layout::ReturnType::Normal
	);
	this->_bootstrapMethod->setValue(1, commandLineArguments);


	
}


// Basic SlotObject creation
Objects::SlotObject* Runtime::ObjectUniverse::createObject(unsigned short slotCount) {
	Object_Layout::ObjectMap* newMap = this->createObjectMap(slotCount);

	return newMap->constructObject(this->_basicAllocator);
}

Objects::SlotObject* Runtime::ObjectUniverse::createObjectWithSlots(unsigned short slotCount, Object_Layout::SlotDescription descriptions[]) {
	Object_Layout::ObjectMap*	newMap = nullptr;
	Objects::SlotObject*			newObject = nullptr;;
	if (slotCount == 1 && descriptions[0].isParent() && descriptions[0].getName()->equalValue("parent", Objects::SymbolType::AlphaNumerical, 0)) {
		return this->_parentMap->constructObject(this->_basicAllocator);
	}
	
	
	newMap = this->createObjectMap(slotCount);
	for (unsigned i = 0; i < slotCount; i++) {
		newMap->setDescription(i, descriptions[i]);
	}

	return newMap->constructObject(this->_basicAllocator);
}

Objects::SlotObject* Runtime::ObjectUniverse::createObjectWithValues(unsigned short slotCount, Object_Layout::SlotDescription description[], Objects::SlotObject* values[]) {
	Objects::SlotObject* newObject = this->createObjectWithSlots(slotCount, description);
	
	for (unsigned i = 0; i < slotCount; i++) {
		newObject->setValue(i, values[i]);
	}

	return newObject;
}

Object_Layout::ObjectMap* Runtime::ObjectUniverse::createObjectMap(unsigned short slotCount) {
	if (slotCount == 0) {
		return this->_emptyMap;
	}	
	return new(this->_basicAllocator) Object_Layout::ObjectMap(slotCount);
}

// Method SlotObject creation
Objects::SlotObject* Runtime::ObjectUniverse::createMethod(unsigned short slotCount) {
	Object_Layout::MethodMap* newMap = this->createMethodMap(slotCount);

	return newMap->constructObject(this->_basicAllocator);
}

Objects::SlotObject* Runtime::ObjectUniverse::createMethodWithSlots(unsigned short slotCount, Object_Layout::SlotDescription descriptions[]) {
	Object_Layout::MethodMap* newMap = nullptr; 
	Objects::SlotObject* newObject = nullptr;;

	newMap = this->createMethodMap(slotCount);
	for (unsigned i = 1; i < newMap->getSlotCount(); i++) {
		newMap->setDescription(i, descriptions[i]);
	}

	return newMap->constructObject(this->_basicAllocator);
}


Objects::SlotObject* Runtime::ObjectUniverse::createMethodWithValues(unsigned short slotCount, Object_Layout::SlotDescription description[], Objects::SlotObject* values[]) {
	Objects::SlotObject* newObject = this->createMethodWithSlots(slotCount, description);
	for (unsigned i = 1; i < newObject->getSlotCount(); i++) {
		newObject->setValue(i, values[i]);
	}

	return newObject;
}


Object_Layout::MethodMap* Runtime::ObjectUniverse::createMethodMap(unsigned short slotCount) {
	Object_Layout::MethodMap* methodMap = new(this->_basicAllocator) Object_Layout::MethodMap(
		slotCount + 1,
		nullptr,
		nullptr,
		Object_Layout::ScopeType::Undefined,
		Object_Layout::ReturnType::Undefined
	);
	methodMap->setDescription(0, Object_Layout::SlotDescription(
		this->createSymbol("me", Objects::SymbolType::AlphaNumerical, 0),
		Object_Layout::SlotType::ParentParameter
	));

	return methodMap;
}



// Specialized SlotObject creation
#define CREATE_OBJ(ObjectName, parameters) Objects::##ObjectName* new##ObjectName = new(this->_basicAllocator) Objects::##ObjectName
#define SHARED_PARAM this->_parentMap
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

Objects::Context* Runtime::ObjectUniverse::createContext(Objects::Context* previous, Objects::SlotObject* reflectee) {
	CREATE_OBJ(Context)(SHARED_PARAM, previous, reflectee);
	SET_TRAIT(newContext, this->_contextTrait);

	return newContext;
}
Objects::Mirror* Runtime::ObjectUniverse::createMirror(Objects::SlotObject* reflectee) {
	CREATE_OBJ(Mirror)(SHARED_PARAM, reflectee);
	SET_TRAIT(newMirror, this->_mirrorTrait);

	return newMirror;
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