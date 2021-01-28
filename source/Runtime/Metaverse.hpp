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

	/* Metaverse is main object of virtual machine
	// It is holding pointers to all part of virtual machine and contains some important methods that are affecting environmnent as whole
	*/
	class Metaverse {
		Memory::MemoryAllocator*		_basicAllocator;
		Memory::MemoryAllocator*		_tenuredAllocator;
		Memory::MemoryAllocator*		_pernamentAllocator;

		Runtime::ObjectUniverse*		_objectUniverse;
		Sending::SendMachine*			_sendMachine;
		Primitives::PrimitiveTable*		_primitiveTable;
		Interpreter::ExecutionEngine*	_executionEngine;

	public:
		Metaverse();
		static Metaverse* create();



	public:
		Memory::MemoryAllocator* getBasicAllocator() { return this->_basicAllocator; };
		Memory::MemoryAllocator* getTenuredAllocator() { return this->_tenuredAllocator; };
		Memory::MemoryAllocator* getPernamentAllocator() { return this->_tenuredAllocator; };

		Runtime::ObjectUniverse* getObjectUniverse() { return this->_objectUniverse; };

		Sending::SendMachine* getSendMachine() { return this->_sendMachine; };
		Interpreter::ExecutionEngine* getExecutionEngine() { return this->_executionEngine; };

	};
}