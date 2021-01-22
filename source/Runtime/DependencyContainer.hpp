#pragma once
namespace Memory {
	class MemoryAllocator;
}
namespace Objects {
	class ObjectFactory;
}
namespace Sending {
	class SendMachine;
}
namespace Interpreter {
	class ExecutionExngine
}


namespace Runtime {
	void initializeVM(int argc, char** argv);
}
namespace Runtime {
	class DependencyContainer {
		friend void Runtime::initializeVM(int argc, char** argv);

		Memory::MemoryAllocator*		_basicAllocator;
		Memory::MemoryAllocator*		_tenuredAllocator;
		Memory::MemoryAllocator*		_pernamentAllocator;
		
		Sending::SendMachine*			_sendMachine;
		Objects::ObjectFactory*			_objectFactory;
		Interpreter::ExecutionEngine*	_executionEngine;
	public:
		DependencyContainer();

	public:
		/*
		Memory::MemoryAllocator* getBasicAllocator()		{ return this->_basicAllocator; };
		Memory::MemoryAllocator* getTenuredAllocator()		{ return this->_tenuredAllocator; };
		Memory::MemoryAllocator* getPernamentAllocator()	{ return this->_tenuredAllocator; };

		Sending::SendMachine* getSendMachine() { return this->_sendMachine; };
		*/
	};
}