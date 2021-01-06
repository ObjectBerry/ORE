#include "../Memory/MemoryAllocator.hpp"

#include "../Object_Layout/MethodInfo.hpp"
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
		activeContext->incIndex();

		if (activeContext->finished()) {
			this->doReturnTop();
		}
	}
}
void Interpreter::ExecutionEngine::doReturnTop() {
	while (true) {
		Object_Layout::MethodInfo* methodInfo = this->getActiveContext()->getReflectee()->getObjectMap()->getMethodInfo();
		this->getActiveProcess()->popContext();
		if (this->getActiveProcess()->hasContexts() == false) {
			// todo: set result of process
			this->pop();
			this->getActiveProcess()->popContext();
			this->_processCycler->removeActiveProcess();
			return;
		}

		if (methodInfo->isImplicit()) {
			continue;
		}

		return;
	}
}
void Interpreter::ExecutionEngine::doPushLiteral() {
	this->getActiveContext()->incIndex();
	unsigned char index = this->getActiveContext()->getBytecode();
	Objects::Object* literalObject = (this->getActiveContext()->getLiteral(index))->clone(this->_clonningAllocator);

	this->push(literalObject);
}
void Interpreter::ExecutionEngine::doPushSelf() {
	this->push(
		this->getActiveContext()->getReflectee()
	);
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

void Interpreter::ExecutionEngine::push(Objects::Object* item) {
	this->getActiveProcess()->push(item);
}
Objects::Object* Interpreter::ExecutionEngine::pop() {
	return this->getActiveProcess()->pop();
}