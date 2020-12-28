#pragma once
namespace Objects {
	class Object;
	class Symbol;
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
	class ObjectMap {
		bool _sharedMap; // this will be used in future to optimization - if map is not shared , it will be beter to only reallocate slots.
		unsigned short _slotCount;
		SlotDescription* _slotDescriptions;
	
	private:
		void* operator new(size_t size, Memory::MemoryAllocator* memoryAllocator);
		ObjectMap(Memory::MemoryAllocator* memoryAllocator, unsigned short slotCount);

	public:
		// factory method used to create object maps
		static ObjectMap*		create(Memory::MemoryAllocator* memoryAllocator, unsigned short slotCount);
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
		
		
	};
}