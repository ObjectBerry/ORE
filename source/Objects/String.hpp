#pragma once
#include "ByteArray.hpp"

namespace Objects {
	class String : public Objects::ByteArray {
	private:
		String(basicParameter, const char* characters);
	public:
		static String*	create(basicParameter, const char* characters);
		String*			clone(Memory::MemoryAllocator* allocator);

	public:
		bool equalObject(Objects::String* other);
		bool equalValue(const char* characters);

	public:
		OBJECT_TYPE(ObjectType::String);

	};
}