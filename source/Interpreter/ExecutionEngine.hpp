#pragma once
namespace Memory {
	class MemoryAllocator;
}
namespace Sending {
	class SendMachine;
}
namespace Primitives {
	class PrimitiveTable;
}
namespace Objects {
	class SlotObject;
	class Context;
	class Process;
}
namespace Runtime {
	class ObjectUniverse;
	class Metaverse;
}

namespace Interpreter {
	class ProcessCycler;
}
namespace Interpreter {
	
	/* Execution Engine is heart of ORE - it is executing methods and cycling between processes
	// It is implemented as switching interpreter - it is slower , but it is cross-platform , unlike threading 
	*///
	class ExecutionEngine {
		Runtime::Metaverse*			_metaverse;
		Runtime::ObjectUniverse*	_objectUniverse;
		Interpreter::ProcessCycler* _processCycler;
		Sending::SendMachine*		_sendMachine;
		Primitives::PrimitiveTable* _primitiveTable;
		Objects::SlotObject**			_parameters;
	
	public:
		ExecutionEngine(Runtime::ObjectUniverse* objectUniverse, Sending::SendMachine* sendMachine, Primitives::PrimitiveTable* primitiveTable);
		ExecutionEngine(Runtime::Metaverse* metaverse);
		Objects::Process* start();  
	
	private: 
		// Instructions
		void doReturnTop();
		void doPushLiteral();
		void doPushSelf();
		void doSend();
		void doVMSend();
		void doSendMyself();
	
	public:
		// method execution
		void pushForExecution(Objects::SlotObject* executableObject, Objects::SlotObject* reciever);
		bool pushParameters(unsigned short parameterCount);

	public:
		// Processes methods
		void haltingError(Objects::SlotObject* error);

	public:
		Objects::Process*	getActiveProcess();
		Objects::Context*	getActiveContext();
		void				push(Objects::SlotObject* item);
		Objects::SlotObject*	pop();

	public:
		inline Interpreter::ProcessCycler* getProcessCycler() { return this->_processCycler; };
	};
}