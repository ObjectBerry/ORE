#pragma once
#include "../Memory/MemoryItem.hpp"
#include "ObjectType.hpp"

namespace Object_Layout {
	class ObjectMap;
}
namespace Objects {
	class ByteArray;
	class ObjectArray;
}

namespace Objects {
	class MappedObject : public Memory::MemoryItem {
		//TODO: Should be refactored
		bool						_visitedObject;
		Objects::ObjectType			_objectType;
		Object_Layout::ObjectMap*	_objectMap;

	protected:
		// Mapped object should not be created independly
		//It is only used to simplify SlotObject class
		MappedObject(Object_Layout::ObjectMap* objectMap);
		Objects::MappedObject* clone(Memory::MemoryAllocator* allocator);
		
	public:
		Object_Layout::ObjectMap*	getObjectMap() { return this->_objectMap; };

		unsigned short				getSlotCount();
		bool						hasCode();
		virtual unsigned short		getParameterCount();
		Objects::ByteArray*			getBytecode();
		Objects::ObjectArray*		getLiterals();

	public:
		Objects::ObjectType getObjectType() { return this->_objectType; };

	};
}