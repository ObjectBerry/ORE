#pragma once
namespace Objects {
	class Object;
}
namespace Sending {
	enum class LookupState {
		OK,
		ZeroResults,
		MultipleResults,
		//InvalidInput
	};

	struct LookupResult {
		Objects::Object*	_resultObject;
		LookupState			_resultState;
	};
}