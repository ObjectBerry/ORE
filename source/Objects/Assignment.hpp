#pragma once
#include "Object.hpp"

namespace Objects {
	class Symbol;
}

namespace Objects {

	/* Assignment object is inspired by same object from Self
	// It have only one job - assign value to slot
	// If you call assignment object , it will take value from stack and save it into slot
	// Slot is specified by field _associatedSlot - it will be saved in slot with same name
	*///
	class Assignment : public Objects::Object {
		Objects::Symbol* _associatedSlot;
		


	
	public:
		Assignment(Object_Layout::ObjectMap* objectMap, Objects::Symbol* associatedSlot);
		virtual Assignment*	clone(Memory::MemoryAllocator* allocator);
	
	public:
		inline Objects::Symbol* getAssociatedSlot() { return this->_associatedSlot; };
		inline unsigned short	getParameterCount() { return 1; }
	
	};
}