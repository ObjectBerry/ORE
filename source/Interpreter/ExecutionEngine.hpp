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
	class ObjectFactory;
	class Object;
	class Context;
	class Process;
}

namespace Interpreter {
	class ProcessCycler;
}
namespace Interpreter {
	class ExecutionEngine {
		Objects::ObjectFactory*		_objectFactory;
		Interpreter::ProcessCycler* _processCycler;
		Sending::SendMachine*		_sendMachine;
		Primitives::PrimitiveTable* _primitiveTable;
		Objects::Object*			_parameters[32];
	
	public:
		ExecutionEngine(Objects::ObjectFactory* objectFactory, Sending::SendMachine* sendMachine, Primitives::PrimitiveTable* primitiveTable);
		void start();
	
	private: 
		// Instructions
		void doReturnTop();
		void doPushLiteral();
		void doPushSelf();
		void doSend();
		void doPrimitiveSend();
		void doSendMyself();
	
	public:
		// method execution
		void pushForExecution(Objects::Object* executableObject, Objects::Object* reciever);
		bool pushParameters(unsigned short parameterCount);

	public:
		Objects::Process*	getActiveProcess();
		Objects::Context*	getActiveContext();
		void				push(Objects::Object* item);
		Objects::Object*	pop();
	};
}