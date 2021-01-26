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
namespace Primitives {
	class PrimitiveTable;
}
namespace Interpreter {
	class ExecutionEngine;
}
namespace Runtime {
	class ObjectUniverse;
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
		
		Runtime::ObjectUniverse*		_objectUniverse;

		Sending::SendMachine*			_sendMachine;
		Objects::ObjectFactory*			_objectFactory;
		Primitives::PrimitiveTable*		_primitiveTable;
		Interpreter::ExecutionEngine*	_executionEngine;

	public:
		
		Memory::MemoryAllocator*		getBasicAllocator()		{ return this->_basicAllocator; };
		Memory::MemoryAllocator*		getTenuredAllocator()	{ return this->_tenuredAllocator; };
		Memory::MemoryAllocator*		getPernamentAllocator()	{ return this->_tenuredAllocator; };

		Runtime::ObjectUniverse*		getObjectUniverse()		{ return this->_objectUniverse; };

		Sending::SendMachine*			getSendMachine()		{ return this->_sendMachine; };		
		Objects::ObjectFactory*			getObjectFactory()		{ return this->_objectFactory; };
		Interpreter::ExecutionEngine*	getExecutionEngine()	{ return this->_executionEngine; };
	};
}