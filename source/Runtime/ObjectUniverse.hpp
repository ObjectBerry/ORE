#pragma once
namespace Memory {
	class MemoryAllocator;
}
namespace Compiler {
	class CodeDescription;
}
namespace Object_Layout {
	class MethodMap;
	class ObjectMap;
	class SlotDescription;
	enum class SlotType : unsigned int;
	enum class ScopeType : unsigned char;
	enum class ReturnType : unsigned char;
}
namespace Objects {
	class Assignment;
	class ByteArray;
	class Code;
	class Context;
	class Mirror;
	class SlotObject;
	class ObjectArray;
	class Process;
	class SmallInt;
	class String;
	class Symbol;
	enum class SymbolType : unsigned short;

}
namespace Runtime {
	class Metaverse;
}

namespace Runtime {
	/* ObjectUniverse is main object of object system
	// It holds prototypes , object structure and system objects (True, False, Undefined)
	// This object will replace ObjectFactory and ObjectWorld
	*///
	class ObjectUniverse {
		// Allocators
		Memory::MemoryAllocator* _basicAllocator;
		Memory::MemoryAllocator* _tenuredAllocator;
		Memory::MemoryAllocator* _pernamentAllocator;
		
		// SlotObject maps
		Object_Layout::ObjectMap* _emptyMap;
		Object_Layout::ObjectMap* _parentMap;
		
		// Structure Objects
		Objects::SlotObject* _lobbyObject;
		Objects::SlotObject* _globalsObject;
		Objects::SlotObject* _traitsObject;
		Objects::SlotObject* _bootstrapMethod;

		// System Objects
		Objects::SlotObject* _trueObject;
		Objects::SlotObject* _falseObject;
		Objects::SlotObject* _undefinedObject;

		// Traits
		Objects::SlotObject* _assignmentTrait;
		Objects::SlotObject* _byteArrayTrait;
		Objects::SlotObject* _contextTrait;
		Objects::SlotObject* _mirrorTrait;
		Objects::SlotObject* _objectArrayTrait;
		Objects::SlotObject* _processTrait; 
		Objects::SlotObject* _smallIntTrait;
		Objects::SlotObject* _stringTrait;
		Objects::SlotObject* _symbolTrait;
		
	
	public:
		ObjectUniverse(Memory::MemoryAllocator* basicAllocator, Memory::MemoryAllocator* tenuredAllocator, Memory::MemoryAllocator* pernamentAllocator);
		ObjectUniverse(Runtime::Metaverse* metaverse); 
		void genesis();
	
	private:
		void initializeTraits(); 
		void initializeMaps();
		void initializeSystemObjects();
		void initializeStructure();

	public:
		void initializeBootstrap(Compiler::CodeDescription codeDescription, Objects::ObjectArray* commandLineArguments);

	public:
		// Simple object creation
		Objects::SlotObject*			createObject(unsigned short slotCount);
		Objects::SlotObject*			createObjectWithSlots(unsigned short slotCount, Object_Layout::SlotDescription descriptions[]);
		Objects::SlotObject*			createObjectWithValues(unsigned short slotCount, Object_Layout::SlotDescription description[], Objects::SlotObject* values[]);
		Object_Layout::ObjectMap*	createObjectMap(unsigned short slotCount);

		// Method creation
		Objects::SlotObject*		  createMethod(unsigned short slotCount);
		Objects::SlotObject*		  createMethodWithSlots(unsigned short slotCount, Object_Layout::SlotDescription description[]);
		Objects::SlotObject*		  createMethodWithValues(unsigned short slotCount, Object_Layout::SlotDescription description[], Objects::SlotObject* values[]);
		Object_Layout::MethodMap* createMethodMap(unsigned short slotCount);

	public:
		// Specialized object creation
		Objects::Assignment*	createAssignment(Objects::Symbol* assignedSlot);
		Objects::ByteArray*		createByteArray(unsigned short arrayLength);
		Objects::Context*		createContext(Objects::Context* previous, Objects::SlotObject* reflectee);
		Objects::Mirror*		createMirror(Objects::SlotObject* reflectee);
		Objects::ObjectArray*	createObjectArray(unsigned short arrayLength);
		Objects::Process*		createProcess(unsigned short stackSize); 
		Objects::SmallInt*		createSmallInt(signed int value);
		Objects::String*		createString(const char* characters);
		Objects::Symbol*		createSymbol(const char* characters, Objects::SymbolType symbolType, unsigned short parameterCount);
	
	public:
		inline Objects::SlotObject* getLobbyObject() { return this->_lobbyObject; };
		inline Objects::SlotObject* getGlobalsObject() { return this->_globalsObject; };
		inline Objects::SlotObject* getTraitsObject() { return this->_traitsObject; };
		inline Objects::SlotObject* getBootstrapMethod() { return this->_bootstrapMethod; };

		inline Objects::SlotObject* getTrueObject()			{ return this->_trueObject; };
		inline Objects::SlotObject* getFalseObject()		{ return this->_falseObject; };
		inline Objects::SlotObject* getUndefinedObject()	{ return this->_undefinedObject; };

	public:
		inline Memory::MemoryAllocator* getAllocator() { return this->_basicAllocator; };
	};
}