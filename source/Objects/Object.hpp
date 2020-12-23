#pragma once
namespace Memory {
	class MemoryFacade;
}
namespace Objects {
	class Object {
		// Object_Laout::ObjectMap _objectMap
		Object** _slotValues;

	public:

		
		void* operator new(size_t size, Memory::MemoryFacade* memoryFacade);
		//Object()


	};
}