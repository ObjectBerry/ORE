#pragma once
namespace Memory {
	class MemoryAllocator;
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
	class Object;
	class ObjectArray;
	class Process;
	class SmallInt;
	class String;
	class Symbol;
	enum class SymbolType : unsigned short;

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
		
		// Object maps
		Object_Layout::ObjectMap* _emptyMap;
		Object_Layout::ObjectMap* _parentMap;
		
		// Structure Objects
		Objects::Object* _lobbyObject;
		Objects::Object* _globalsObject;
		Objects::Object* _traitsObject;

		// System Objects
		Objects::Object* _trueObject;
		Objects::Object* _falseObject;
		Objects::Object* _undefinedObject;

		// Traits
		Objects::Object* _assignmentTrait;
		Objects::Object* _byteArrayTrait;
		Objects::Object* _contextTrait;
		Objects::Object* _objectArrayTrait;
		Objects::Object* _processTrait; 
		Objects::Object* _smallIntTrait;
		Objects::Object* _stringTrait;
		Objects::Object* _symbolTrait;
		
	
	public:
		ObjectUniverse(Memory::MemoryAllocator* basicAllocator, Memory::MemoryAllocator* tenuredAllocator, Memory::MemoryAllocator* pernamentAllocator);
		void genesis();
	
	private:
		void initializeTraits(); 
		void initializeMaps();
		void initializeSystemObjects();
		void initializeStructure();

	public:
		// Simple object creation
		Objects::Object*			createObject(unsigned short slotCount);
		Objects::Object*			createObjectWithSlots(unsigned short slotCount, Object_Layout::SlotDescription descriptions[]);
		Objects::Object*			createObjectWithValues(unsigned short slotCount, Object_Layout::SlotDescription description[], Objects::Object* values[]);
		Object_Layout::ObjectMap*	createObjectMap(unsigned short slotCount);

	public:
		// Specialized object creation
		Objects::Assignment*	createAssignment(Objects::Symbol* assignedSlot);
		Objects::ByteArray*		createByteArray(unsigned short arrayLength);
		Objects::Context*		createContext(Objects::Context* previous, Objects::Object* reflectee);
		Objects::ObjectArray*	createObjectArray(unsigned short arrayLength);
		Objects::Process*		createProcess(unsigned short stackSize);
		Objects::SmallInt*		createSmallInt(signed int value);
		Objects::String*		createString(const char* characters);
		Objects::Symbol*		createSymbol(const char* characters, Objects::SymbolType symbolType, unsigned short parameterCount);
	
	public:
		inline Objects::Object* getLobbyObject() { return this->_lobbyObject; };
		inline Objects::Object* getGlobalsObject() { return this->_lobbyObject; };
		inline Objects::Object* getTraitsObject() { return this->_lobbyObject; };
		
		inline Objects::Object* getTrueObject()			{ return this->_trueObject; };
		inline Objects::Object* getFalseObject()		{ return this->_falseObject; };
		inline Objects::Object* getUndefinedObject()	{ return this->_undefinedObject; };
	};
}