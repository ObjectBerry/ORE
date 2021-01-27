#pragma once
#include "Object.hpp"

namespace Objects {

	/* Object that is representing 32-bit signed integer
	// Really small object , just getter for integer and comparing operations
	// TODO: There is possibility to cache this object to improve performance 
	*///
	class SmallInt : public Objects::Object {
		signed int _value;

	private:
		SmallInt(basicParameter, signed int value);
	public:
		static SmallInt*	create(basicParameter, signed int value);
		virtual SmallInt*	clone(Memory::MemoryAllocator* allocator);
		
	public:
		bool equalObject(SmallInt* other);
		bool equalValue(signed int integer);

		inline signed int getValue() { return this->_value; };
	
	public:
		OBJECT_TYPE(ObjectType::SmallInt);
	};
}