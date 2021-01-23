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


namespace Objects {
	class ObjectFactory {
		Memory::MemoryAllocator* _normalAllocator;
		Memory::MemoryAllocator* _pernamentAllocator;

		// TODO: this all can be reduced to one map
		// i will leaave it here for optimization stage
		Object_Layout::ObjectMap* _assignmentMap;
		Object_Layout::ObjectMap* _byteArrayMap;
		Object_Layout::ObjectMap* _codeMap;
		Object_Layout::ObjectMap* _contextMap;
		Object_Layout::ObjectMap* _objectArrayMap;
		Object_Layout::ObjectMap* _processMap;
		Object_Layout::ObjectMap* _smallIntMap;
		Object_Layout::ObjectMap* _stringMap;
		Object_Layout::ObjectMap* _symbolMap;

	private:
		void initializeMaps();

	public:
		ObjectFactory(Memory::MemoryAllocator* normalAllocator, Memory::MemoryAllocator* _pernamentAllocator);
		
		Objects::Assignment*	createAssignment(Objects::Symbol* assignedSlot);
		Objects::ByteArray*		createByteArray(unsigned short arrayLength);
		Objects::Code*			createCode(Objects::ByteArray* bytecodes, Objects::ObjectArray* literals); 
		Objects::Context*		createContext(Objects::Context* previous, Objects::Object* reflectee);
		Objects::ObjectArray*	createObjectArray(unsigned short arrayLength);
		Objects::Process*		createProcess(unsigned short stackSize);
		Objects::SmallInt*		createSmallInt(signed int value);
		Objects::String*		createString(const char* characters);
		Objects::Symbol*		createSymbol(const char* characters, Objects::SymbolType symbolType, unsigned short parameterCount);
	
		Object_Layout::ObjectMap*		createObjectMap(unsigned short slotCount);
		Object_Layout::MethodMap*		createMethodMap(unsigned short slotCount, Objects::ByteArray* bytecodes, Objects::ObjectArray* literals, Object_Layout::ScopeType scopeType, Object_Layout::ReturnType returnType);
	public:
		inline Memory::MemoryAllocator* getAllocator() { return this->_normalAllocator; };
	};
}