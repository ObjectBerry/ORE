#pragma once

namespace Object_Layout {
	
	/* Slot types are used to represent types of slot
	// It is showing us if slot is parent slot or parameter of method
	*///
	enum class SlotType : unsigned int {
		NormalSlot,
		ParentSlot,
		NormalParameter,
		ParentParameter,

		UnititalizedSlot
	};


};