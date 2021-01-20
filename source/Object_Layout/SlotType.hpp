#pragma once

namespace Object_Layout {
	
	/* Slot types are used to represent types of slot
	// It is showing us if slot is parent slot or parameter of method
	*///
	enum class SlotType : unsigned int {
		NormalSlot  = 0xAA,
		ParentSlot  = 0xAF,
		NormalParameter = 0xFA,
		ParentParameter = 0xFF,

		UnititalizedSlot = 0x00
	};


};