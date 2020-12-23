#pragma once

namespace Memory {
	class MemoryFacade;
}
namespace Objects {
	class Object;
}
namespace Object_Layout {
	class SlotDescription {
		// Objects::Symbol* _slotName
		// Object_Layout::SlotType _slotType
		Objects::Object* slotData;

	public:
		
		void* operator new[](size_t size, Memory::MemoryFacade* memoryFacade);
		SlotDescription();
	};
}