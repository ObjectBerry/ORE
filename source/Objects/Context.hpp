#pragma once
#include "Object.hpp"

namespace Objects {
	/* This is object that is holding namespace of evaluated method
	// It contains pointer to method , pointer to previous and pointer to process(process is not implemented tho)
	// Contexts are organized into cactus stack with only one branch
	*///
	class Context : public Objects::Object {
		Context*			_previous;
		Objects::Object*	_reflectee; // object that is executed

	};
}