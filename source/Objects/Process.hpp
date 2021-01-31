#pragma once
#include "Object.hpp"
namespace Objects {
	class ObjectArray;
	class Context;
}

namespace Objects {

	/* This is Process ( Fiber would be better name)
	// It is basis of ORE multitasking - it have own item stack and cactus stack for methods 
	// It is supporting cooperative multitasking using Process cycler and primitive methods
	*/
	class Process : public Objects::Object {
		unsigned short			_stackTop;
		Objects::ObjectArray*	_objectStack;
		Objects::Context*		_activeContext;

		Objects::Object*		_processResult;
		bool					_errorResult;

		// Process acts as node in double linked circular list
		Objects::Process*		_nextProcess;
		Objects::Process*		_prevProcess;
	
	private:
		Process(basicParameter, Objects::ObjectArray* objectStack);

	public:
		Process(Object_Layout::ObjectMap* objectMap, Objects::ObjectArray* objectStack);

		static Process*  create(basicParameter, Objects::ObjectArray* objectStack);
		virtual Process* clone(Memory::MemoryAllocator* allocator);

	public:
		// Object stack operations
		void						push(Objects::Object* item);
		Objects::Object*			pop();
		bool						isStackFull();

	public:
		// Context stack operations
		void						pushContext(Objects::Context* context);
		Objects::Context*			popContext();
		inline Objects::Context*	peekContext() { return this->_activeContext; }
		inline bool					hasContexts() { return this->_activeContext != nullptr; };

	public:
		// Result operations
		void					clearProcessResult();
		void					setProcessResult(Objects::Object* processResult, bool errorResult);
		inline Objects::Object* getProcessResult()		{ return this->_processResult; };
		inline bool             isFinished()			{ return this->_processResult != nullptr; };
		inline bool				isFinishedWithError()	{ return this->_errorResult; };
		


	public:
		// Linked list operations
		inline Objects::Process*	getNextProcess() { return this->_nextProcess; }
		inline Objects::Process*	getPrevProcess() { return this->_prevProcess; }
		inline void					setNextProcess(Objects::Process* process) { this->_nextProcess = process; }
		inline void					setPrevProcess(Objects::Process* process) { this->_prevProcess = process; }
	
	public:
		OBJECT_TYPE(ObjectType::Process);
	};
}