#pragma once
#include "Object.hpp"

namespace Objects {
	class Mirror : public Objects::Object {
		Objects::Object* _reflectee;
	

	public:
		Mirror(Object_Layout::ObjectMap* objectMap, Objects::Object* reflectee);
		Mirror*			clone(Memory::MemoryAllocator* allocator);

	public:
		inline Objects::Object* getReflectee() { return this->_reflectee; };


	};
}