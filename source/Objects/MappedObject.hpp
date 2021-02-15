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
	protected:
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

		inline void				setVisitedObject(bool visitedValue) { this->_visitedObject = visitedValue; };
		inline bool				getVisitedObject() { return this->_visitedObject; };
	
		inline bool				identical(Objects::MappedObject* other) { return this == other; };
	public:
		void setObjectType(Objects::ObjectType objType) { this->_objectType = objType; };
		Objects::ObjectType getType() { return this->_objectType; };

	};
}