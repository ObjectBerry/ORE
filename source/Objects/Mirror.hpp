#pragma once
#include "Object.hpp"

namespace Objects {
	class Mirror : public Objects::Object {
		Objects::Object* reflectee;
	
	private:
		Mirror(basicParameter, Objects::Object* reflectee);

	public:
		static Mirror*	create(basicParameter, Objects::Object* reflectee);
		Mirror*			clone(Memory::MemoryAllocator* allocator);

	public:
		OBJECT_TYPE(ObjectType::Mirror);
	};
}