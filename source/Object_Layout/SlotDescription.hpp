#pragma once

namespace Memory {
	class MemoryAllocator;
}
namespace Objects {
	class SlotObject;
	class Symbol;
}
namespace Object_Layout {
	enum class SlotType : unsigned int;

}


namespace Object_Layout {

	/* This is class that contain description for slot (slot name and slot type )
	// It is used in SlotObject Map . Value of slot is not in slot description - it is in SlotObject field called  _values.
	*///
	class SlotDescription {
		Objects::Symbol*		_slotName;
		Object_Layout::SlotType _slotType;

	public:
		
		void* operator new[](size_t size, Memory::MemoryAllocator* memoryAllocator);
		SlotDescription();
		SlotDescription(Objects::Symbol* slotName, Object_Layout::SlotType slotType);

		void setAll(Objects::Symbol* _slotName,  Object_Layout::SlotType _slotType);
	
	public:
		bool equalSlot(SlotDescription* other);
		bool equalName(Objects::Symbol* otherSymbol);
		bool isParameter();
		bool isParent();
		bool isValid();

		inline Objects::Symbol* getName() { return this->_slotName; };
	};
}