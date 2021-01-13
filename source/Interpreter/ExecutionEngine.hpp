#pragma once
namespace Memory {
	class MemoryAllocator;
}
namespace Sending {
	class SendMachine;
}
namespace Objects {
	class Object;
	class Context;
	class Process;
}

namespace Interpreter {
	class ProcessCycler;
}
namespace Interpreter {
	class ExecutionEngine {
		Memory::MemoryAllocator*	_clonningAllocator;
		Interpreter::ProcessCycler* _processCycler;
		Sending::SendMachine*		_sendMachine;
		Objects::Object*			_parameters[32];
	
	public:
		ExecutionEngine(Memory::MemoryAllocator* clonningAllocator,  Interpreter::ProcessCycler* processCycler, Sending::SendMachine* sendMachine);
		void start();
	
	private: 
		// Instructions
		void doReturnTop();
		void doPushLiteral();
		void doPushSelf();
		void doSend();
		void doSendMyself();
	
	public:
		// method execution
		void pushForExecution(Objects::Object* executableObject, Objects::Object* reciever);

	public:
		Objects::Process*	getActiveProcess();
		Objects::Context*	getActiveContext();
		void				push(Objects::Object* item);
		Objects::Object*	pop();
	};
}