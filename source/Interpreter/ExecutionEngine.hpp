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
	class Object;
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
		Objects::Object**			_parameters;
	
	public:
		ExecutionEngine(Runtime::ObjectUniverse* objectUniverse, Sending::SendMachine* sendMachine, Primitives::PrimitiveTable* primitiveTable);
		ExecutionEngine(Runtime::Metaverse* metaverse);
		void start();
	
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
		void pushForExecution(Objects::Object* executableObject, Objects::Object* reciever);
		bool pushParameters(unsigned short parameterCount);

	public:
		// Processes methods
		void removeProcess();
		void haltingError(Objects::Object* error);

	public:
		Objects::Process*	getActiveProcess();
		Objects::Context*	getActiveContext();
		void				push(Objects::Object* item);
		Objects::Object*	pop();

	public:
		inline Interpreter::ProcessCycler* getProcessCycler() { return this->_processCycler; };
	};
}