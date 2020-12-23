#pragma once
namespace Memory {
	class MemoryFacade;
}
namespace Object_Layout {
	class ObjectMap;
}


namespace Objects {
	class Object {
		Object_Layout::ObjectMap* _objectMap;
		Object** _slotValues;

	protected:
		void* operator new(size_t size, Memory::MemoryFacade* memoryFacade);
		Object(Memory::MemoryFacade* memoryFacade, Object_Layout::ObjectMap* objectMap);
	
	public:
		static Object* create(Memory::MemoryFacade* memoryFacade, Object_Layout::ObjectMap* objectMap);
		
		


	};
}