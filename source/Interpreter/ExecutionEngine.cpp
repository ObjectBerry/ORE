#include "../Memory/MemoryAllocator.hpp"

#include "../Sending/LookupResult.hpp"
#include "../Sending/SendMachine.hpp"

#include "../Object_Layout/ExecutableMap.hpp"
#include "../Object_Layout/ObjectMap.hpp"
#include "../Object_Layout/SlotIterator.hpp"
#include "../Object_Layout/SlotDescription.hpp"

#include "../Objects/Object.hpp"
#include "../Objects/Context.hpp"
#include "../Objects/Process.hpp"
#include "../Objects/Symbol.hpp"
#include "../Objects/Assignment.hpp"

#include "Bytecodes.hpp"
#include "ProcessCycler.hpp"
#include "ExecutionEngine.hpp"


Interpreter::ExecutionEngine::ExecutionEngine(Memory::MemoryAllocator* clonningAllocator, Interpreter::ProcessCycler* processCycler, Sending::SendMachine* sendMachine) {
	this->_clonningAllocator	= clonningAllocator;
	this->_processCycler		= processCycler;
	this->_sendMachine			= sendMachine;
	
	
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
		Object_Layout::ReturnType returnType = reinterpret_cast<Object_Layout::ExecutableMap*>(this->getActiveContext()->getReflectee()->getObjectMap())->getReturnType();
		this->getActiveProcess()->popContext();
		if (this->getActiveProcess()->hasContexts() == false) {
			// todo: set result of process
			this->pop();
			this->getActiveProcess()->popContext();
			this->_processCycler->removeActiveProcess();
			return;
		}

		if (returnType == Object_Layout::ReturnType::Implicit) {
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
	Objects::Symbol* messageSelector;
	Objects::Object* messageReciever;
	
	Objects::Object* tmp = this->pop();
	if (tmp->getType() != Objects::ObjectType::Symbol)
		return;
	
	messageSelector = reinterpret_cast<Objects::Symbol*>(tmp);
	messageReciever = this->pop(); 

	Sending::LookupResult lookupResult = this->_sendMachine->sendMessage(messageReciever, messageSelector, false);

	if (lookupResult._resultState != Sending::LookupState::OK) {
		// handle error
		return;
	}

	Objects::Object* result = lookupResult._resultObject;
	


	if (result->hasCode()) {
		this->pushForExecution(result, messageReciever);
	}
	else if (result->getType() == Objects::ObjectType::Assignment) {
		// object assignment
	}
	else {
	   // data object
		this->push(result);
	}
}

void Interpreter::ExecutionEngine::doSendMyself() {
	this->doPushSelf();
	this->doSend();
}

// Executable methods

void Interpreter::ExecutionEngine::pushForExecution(Objects::Object* executableObject, Objects::Object* reciever) {
	// TODO: do this 
}


// shortcuts for some most used object primitives
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
