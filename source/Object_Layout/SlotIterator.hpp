#pragma once
namespace Object_Layout {
	class SlotDescription;
	class ObjectMap;
}
namespace Object_Layout {

	// This is slot iterator 
	// It can be used to iterate over slot descriptions in Object Map.
	// Allocate only on stack - there isnt any reasont to allocate this on heap
	class SlotIterator {
		SlotDescription* _activeDescription;
		SlotDescription* _lastDescription;
		
	public:
		SlotIterator(ObjectMap* iteratedMap);

		SlotDescription*	nextItem();
		bool				isEnd();
	};
}