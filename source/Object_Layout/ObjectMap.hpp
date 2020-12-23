#pragma once
namespace Objects {
	class Object;
}
namespace Memory {
	class MemoryFacade;
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
		void* operator new(size_t size, Memory::MemoryFacade* memoryFacade);
		ObjectMap(Memory::MemoryFacade* memoryFacade, unsigned short slotCount);

	public:
		// factory method used to create object maps
		static ObjectMap* create(Memory::MemoryFacade* memoryFacade, unsigned short slotCount);

		ObjectMap* clone(Memory::MemoryFacade* memoryFacade);

	};
}