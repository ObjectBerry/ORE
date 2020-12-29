#pragma once
#include "Object.hpp"

namespace Objects {
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
	};
}