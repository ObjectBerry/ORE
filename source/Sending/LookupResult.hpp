#pragma once
namespace Objects {
	class SlotObject;
}
namespace Sending {

	/* Lookup state is specifing result of object lookup (evaluated by SendMachine)
	// There are 3 result state and 1 state that is used only during development
	//  +             OK : Lookup was succesfull , we will return founded object
	//  +    ZeroResults : Slot with searched name was not found during lookup
	//  + MultipleResult : There are multiple slots with same name in one generation ( unlike Self, there CAN be duplicated slots if they are in different generations)
	//  +  InvalidResult : Used during development and testing - it is placeholder state during implementation of new methods
	*///
	enum class LookupState {
		OK,
		ZeroResults,
		MultipleResults,
		InvalidResult
	};

	/* Lookup result is returned by lookup method
	// It contains lookup state and object that was found by lookup
	*///
	struct LookupResult {
		Objects::SlotObject*	_resultObject;
		LookupState			_resultState;
	};
}