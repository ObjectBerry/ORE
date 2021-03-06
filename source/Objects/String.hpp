#pragma once
#include "ByteArray.hpp"

namespace Objects {

	/* String is special version of ByteArray - it is used to store characters specifically
	// It probably cant support unicode - we will fix this problem in future
	// TODO: Add support for UTF-16
	*/
	class String : public Objects::ByteArray {
	public:
		String(Object_Layout::ObjectMap* objectMap, const char* characters);
		virtual String*	clone(Memory::MemoryAllocator* allocator);

	public:
		bool equalObject(Objects::String* other);
		bool equalValue(const char* characters);

	};
}