#pragma once
#include "Object.hpp"

namespace Objects {
	/* This is object that is holding namespace of evaluated method
	// It contains pointer to method , pointer to previous and pointer to process(process is not implemented tho)
	// Contexts are organized into cactus stack with only one branch
	*///
	class Context : public Objects::Object {
		unsigned short		_bytecodeIndex;
		Context*			_previous;
		Objects::Object*	_reflectee; // object that is executed
		//Objects::Process* _myProcess
	
	private:
		Context(basicParameter, Context* previous, Objects::Object* reflectee);

	public:
		static Context* create(basicParameter, Context* previous, Objects::Object* reflectee);

		Context* clone(Memory::MemoryAllocator* allocator);
		Context* subContext(Memory::MemoryAllocator* allocator, Objects::Object* reflectee);
	public:
		// Code manipulation
		char				getBytecode();
		Objects::Object*	getLiteral(unsigned short index);
		

		void				incIndex();
		void				setIndex(unsigned short newIndex);
		char				getIndex();
		bool				finished();


	public:
		inline Objects::Object* getReflectee() { return this->_reflectee; };
		inline bool				isRootContext() { return (this->_previous == nullptr); }
		inline void             setPrevious(Context* context) { this->_previous = context; };
		inline Context*			getPrevious() { return this->_previous; };

	public:
		OBJECT_TYPE(ObjectType::Context);
	};
}