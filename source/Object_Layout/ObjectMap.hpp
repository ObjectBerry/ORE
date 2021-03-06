#pragma once
#include "../Memory/MemoryItem.hpp"

namespace Objects {
	class SlotObject;
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

	/* SlotObject map is shared format of all objects
	// When we create new object using clonning , they will have same map - map will change only when we add or delete slot
	// SlotObject map contains only names and types of slots - values saved on slots are stored in _values of Objects:SlotObject
	*///
	class ObjectMap : public Memory::MemoryItem {
	protected:
		// this will be used in future to optimization - 
		// if map is not shared , it will be better to only reallocate new slots than creating whole new map
		bool				_sharedMap; 

		unsigned short		_slotCount;
		SlotDescription*	_slotDescriptions;
	
	public:
		ObjectMap(unsigned short slotCount);
		virtual ObjectMap*		clone(Memory::MemoryAllocator* memoryAllocator);
		
		Objects::SlotObject*		constructObject(Memory::MemoryAllocator* memoryAllocator);
		

	public:
		SlotDescription*		getDescription(unsigned short index);
		virtual void			setDescription(unsigned short index, SlotDescription slotDescription);
		SlotIterator			getIterator();
	
		signed int				getSlotIndex(Objects::Symbol* slotName);

	public:
		inline unsigned short	getSlotCount() { return this->_slotCount; }
		inline SlotDescription* getSlotDescriptions() { return this->_slotDescriptions; }
	
	public:
		//code methods
		virtual bool hasCode() { return false; };


	};
}