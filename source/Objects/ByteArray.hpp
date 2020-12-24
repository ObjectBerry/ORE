#pragma once
#include "Object.hpp"

namespace Objects {
	class ByteArray : public Objects::Object {
		unsigned short length;

	protected:

		ByteArray();
	public:
		ByteArray* create(Memory::MemoryAllocator* allocator, Object_Layout::ObjectMap* objectMap, unsigned short length);

	public:
		OBJECT_TYPE(ObjectType::ByteArray);
	};
}