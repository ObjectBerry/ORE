#pragma once
#include "Object.hpp"

namespace Objects {

	/* Object that is representing 32-bit signed integer
	// Really small object , just getter for inteher and comparing operations
	// Should be cached too 
	*/
	class SmallInt : public Objects::Object {
		signed int _value;

	private:
		SmallInt(basicParameter, signed int value);
	public:
		static SmallInt*	create(basicParameter, signed int value);
		SmallInt*			clone(Memory::MemoryAllocator* allocator);
		
	public:
		bool equalObject(SmallInt* other);
		bool equalValue(signed int integer);

		inline signed int getValue() { return this->_value; };
	
	public:
		OBJECT_TYPE(ObjectType::SmallInt);
	};
}