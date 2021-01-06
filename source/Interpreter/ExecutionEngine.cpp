#include "../Memory/MemoryAllocator.hpp"

#include "../Object_Layout/ObjectMap.hpp"
#include "../Objects/Object.hpp"
#include "../Objects/Context.hpp"
#include "../Objects/Process.hpp"

#include "Bytecodes.hpp"
#include "ProcessCycler.hpp"
#include "ExecutionEngine.hpp"


Interpreter::ExecutionEngine::ExecutionEngine(Memory::MemoryAllocator* clonningAllocator, Interpreter::ProcessCycler* processCycler)  {
	this->_clonningAllocator = clonningAllocator;
	this->_processCycler = processCycler;
	
}

void Interpreter::ExecutionEngine::start() {
	while (this->_processCycler->hasProcesses()) {
		
		Objects::Context* activeContext = this->getActiveContext();
		unsigned char bytecode = activeContext->getBytecode();

		switch ((Interpreter::Bytecodes::Instructions)bytecode) {

		case Interpreter::Bytecodes::Instructions::ReturnTop:
			this->doReturnTop();
			break;

		case Interpreter::Bytecodes::Instructions::PushLiteral: 
			this->doPushLiteral();
			activeContext->incIndex();
			break;

		case Interpreter::Bytecodes::Instructions::PushSelf:
			this->doPushSelf();
			break;

		case Interpreter::Bytecodes::Instructions::Send:
			this->doSend();
			break;

		case Interpreter::Bytecodes::Instructions::SendMyself: 
			this->doSendMyself(); 
			break;

		default:
			// Todo: halting error
			break;

		}

		if (activeContext->finished()) {
			this->doReturnTop();
		}
	}
}
void Interpreter::ExecutionEngine::doReturnTop() {

}
void Interpreter::ExecutionEngine::doPushLiteral() {

}
void Interpreter::ExecutionEngine::doPushSelf() {

}
void Interpreter::ExecutionEngine::doSend() {
	
}
void Interpreter::ExecutionEngine::doSendMyself() {

}


Objects::Process* Interpreter::ExecutionEngine::getActiveProcess() {
	return this->_processCycler->getActiveProcess(); 
}
Objects::Context* Interpreter::ExecutionEngine::getActiveContext() {
	return this->getActiveProcess()->peekContext(); 
}