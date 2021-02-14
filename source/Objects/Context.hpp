#pragma once
#include "SlotObject.hpp"

namespace Objects {
	/* This is object that is holding namespace of evaluated method
	// It contains pointer to method , pointer to previous and pointer to process(process is not implemented tho)
	// Contexts are organized into cactus stack with only one branch
	*///
	class Context : public Objects::SlotObject {
		unsigned short		_bytecodeIndex;
		Context*			_previous;
		Objects::SlotObject*	_reflectee; // object that is executed
		//Objects::Process* _myProcess
	

	public:
		Context(Object_Layout::ObjectMap* objectMap, Context* previous, Objects::SlotObject* reflectee);
		virtual Context*	clone(Memory::MemoryAllocator* allocator);

	public:
		// Code manipulation
		char				getBytecode();
		Objects::SlotObject*	getLiteral(unsigned short index);
		

		void				incIndex();
		void				setIndex(unsigned short newIndex);
		char				getIndex();
		bool				finished();


	public:
		inline Objects::SlotObject* getReflectee() { return this->_reflectee; };
		inline bool				isRootContext() { return (this->_previous == nullptr); }
		inline void             setPrevious(Context* context) { this->_previous = context; };
		inline Context*			getPrevious() { return this->_previous; };

	};
}