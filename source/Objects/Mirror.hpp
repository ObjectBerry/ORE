#pragma once
#include "SlotObject.hpp"

namespace Objects {
	class Mirror : public Objects::SlotObject {
		Objects::SlotObject* _reflectee;
	

	public:
		Mirror(Object_Layout::ObjectMap* objectMap, Objects::SlotObject* reflectee);
		Mirror*			clone(Memory::MemoryAllocator* allocator);

	public:
		inline Objects::SlotObject* getReflectee() { return this->_reflectee; };


	};
}