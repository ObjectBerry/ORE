#pragma once
#include "MethodInfo.hpp"

namespace Objects {
	class Object;
	class Symbol;
	class Code;
}
namespace Memory {
	class MemoryAllocator;
}
namespace Object_Layout {
	class SlotIterator;
	class SlotDescription;
	enum class SlotType : unsigned int;
}

namespace Object_Layout {

	/* Object map is shared format of all objects
	// When we create new object using clonning , they will have same map - map will change only when we add or delete slot
	// Object map contains only names and types of slots - values saved on slots are stored in _values of Objects:Object
	*///
	class ObjectMap {
		bool				_sharedMap; // this will be used in future to optimization - if map is not shared , it will be beter to only reallocate slots.
		unsigned short		_slotCount;
		SlotDescription*	_slotDescriptions;
	
		// code description
		// this should be refactored into own object and replaced by pointer to that object
		Objects::Code*				_objectCode;
		Object_Layout::MethodInfo*	_methodInfo;
		unsigned char				_parameterCount;

	private:
		void* operator new(size_t size, Memory::MemoryAllocator* memoryAllocator);
		ObjectMap(Memory::MemoryAllocator* memoryAllocator, unsigned short slotCount);

	public:
		// factory method used to create object maps
		static ObjectMap*		create(Memory::MemoryAllocator* memoryAllocator, unsigned short slotCount);
		static ObjectMap*		createMethod(Memory::MemoryAllocator* allocator, unsigned short slotCount, SlotDescription scopeLink, Objects::Code* code, Object_Layout::MethodInfo* methodInfo);
		
		ObjectMap*				clone(Memory::MemoryAllocator* memoryAllocator);
		Objects::Object*		constructObject(Memory::MemoryAllocator* memoryAllocator);
	
	public:
		SlotDescription*		getDescription(unsigned short index);
		void					setDescription(unsigned short index, SlotDescription slotDescription);
		SlotIterator			getIterator();
	
		signed int				getSlotIndex(Objects::Symbol* slotName);

	public:
		inline unsigned short	getSlotCount() { return this->_slotCount; }
		inline SlotDescription* getSlotDescriptions() { return this->_slotDescriptions; }
	
	public:
		//code methods
		
		
		inline bool							hasCode() { return this->_objectCode != nullptr; };
		inline Objects::Code*				getCode() { return this->_objectCode; };
		inline Object_Layout::MethodInfo*	getMethodInfo() { return this->_methodInfo; };
		inline unsigned char				getParameterCount() { return this->_parameterCount; };

		// this should be moved into private + add Objects::Object
		// only object should call this methods
		void								addCode(Objects::Code* code, Object_Layout::MethodInfo* methodInfo);
		void								setCode(Objects::Code* code);
		void								setMethodInfo(MethodInfo* methodInfo) { this->_methodInfo = methodInfo; };
	};
}