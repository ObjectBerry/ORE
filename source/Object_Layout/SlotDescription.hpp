#pragma once

namespace Memory {
	class MemoryFacade;
}
namespace Objects {
	class Object;
}
namespace Object_Layout {
	enum class SlotType : unsigned int;

}


namespace Object_Layout {
	// This is class that contain description for slot (slot name and slot type )
	// It is used in Object Map . Value of slot is not in slot description - it is in Object.
	class SlotDescription {
		// Objects::Symbol*		_slotName
		Object_Layout::SlotType _slotType;

	public:
		
		void* operator new[](size_t size, Memory::MemoryFacade* memoryFacade);
		SlotDescription();

		void setAll(/*Objects::Symbol* _slotName, */ Object_Layout::SlotType _slotType);
	};
}