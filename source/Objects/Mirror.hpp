#pragma once
#include "Object.hpp"

namespace Objects {
	class Mirror : public Objects::Object {
		Objects::Object* _reflectee;
	
	private:
		Mirror(basicParameter, Objects::Object* reflectee);

	public:
		Mirror(Object_Layout::ObjectMap* objectMap, Objects::Object* reflectee);

		static Mirror*	create(basicParameter, Objects::Object* reflectee);
		Mirror*			clone(Memory::MemoryAllocator* allocator);

	public:
		OBJECT_TYPE(ObjectType::Mirror);
	};
}