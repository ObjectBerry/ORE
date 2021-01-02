#pragma once
#include "Object.hpp"

namespace Objects {
	class Symbol;
}

namespace Objects {
	class Assignment : public Objects::Object {
		Objects::Symbol* _associatedSlot;
		
	private:
		Assignment(basicParameter, Objects::Symbol* associatedSlot);
	
	public:
		static Assignment*	create(basicParameter, Objects::Symbol* associatedSlot);
		Assignment*			clone(Memory::MemoryAllocator* allocator);
	
	public:
		inline Objects::Symbol* getAssociatedSlot() { return this->_associatedSlot; };

	public:
		OBJECT_TYPE(ObjectType::Assignment);
	};
}