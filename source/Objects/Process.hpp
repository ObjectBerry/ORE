#pragma once
#include "Object.hpp"
namespace Objects {
	class ObjectArray;
	class Context;
}

namespace Objects {
	class Process : public Objects::Object {
		unsigned short			_stackTop;
		Objects::ObjectArray*	_objectStack;
		Objects::Context*		_activeContext;

		// TODO: Process result
		// Process acts as node in double linked circular list
		Objects::Process*		_nextProcess;
		Objects::Process*		_prevProcess;
	
	private:
		Process(basicParameter, Objects::ObjectArray* objectStack);

	public:
		static Process* create(basicParameter, Objects::ObjectArray* objectStack);
		Process* clone(Memory::MemoryAllocator* allocator);

	public:
		// Object stack operations
		void						push(Objects::Object* item);
		Objects::Object*			pop();
		bool						isStackFull();

	public:
		// Context stack operations
		void						createContext(Memory::MemoryAllocator* allocator, Objects::Object* method);
		void						pushContext(Objects::Context* context);
		Objects::Context*			popContext();
		inline Objects::Context*	peekContext() { return this->_activeContext; }
		inline bool					hasContexts() { return this->_activeContext != nullptr; };

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