#pragma once
namespace Objects {
	class Object;
}
namespace Memory {
	class MemoryAllocator;
}
namespace Object_Layout {
	class SlotDescription;
	enum class SlotType : unsigned int;
}

namespace Object_Layout {
	class ObjectMap {
		bool _sharedMap;
		unsigned short _slotCount;
		SlotDescription* _slotDescriptions;
	
	private:
		void* operator new(size_t size, Memory::MemoryAllocator* memoryAllocator);
		ObjectMap(Memory::MemoryAllocator* memoryAllocator, unsigned short slotCount);

	public:
		// factory method used to create object maps
		static ObjectMap* create(Memory::MemoryAllocator* memoryAllocator, unsigned short slotCount);
		ObjectMap* clone(Memory::MemoryAllocator* memoryAllocator);

		Objects::Object* constructObject(Memory::MemoryAllocator* memoryAllocator);
	
	public:
		
		SlotDescription* getDescription(unsigned short index);
		void setDescription(unsigned short index, SlotDescription slotDescription);

	public:
		inline unsigned short getSlotCount() { return this->_slotCount; }
		inline SlotDescription* getSlotDescriptions() { return this->_slotDescriptions; }
		
	};
}