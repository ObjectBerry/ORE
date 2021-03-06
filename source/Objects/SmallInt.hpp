#pragma once
#include "SlotObject.hpp"

namespace Objects {

	/* SlotObject that is representing 32-bit signed integer
	// Really small object , just getter for integer and comparing operations
	// TODO: There is possibility to cache this object to improve performance 
	*///
	class SmallInt : public Objects::SlotObject {
		signed int _value;


	public:
		SmallInt(Object_Layout::ObjectMap* objectMap, signed int value);
		virtual SmallInt*	clone(Memory::MemoryAllocator* allocator);
		
	public:
		bool equalObject(SmallInt* other);
		bool equalValue(signed int integer);

		inline signed int getValue() { return this->_value; };
	
	};
}