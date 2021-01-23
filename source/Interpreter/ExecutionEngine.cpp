#include "../Memory/MemoryAllocator.hpp"

#include "../Runtime/DependencyContainer.hpp"
#include "../Runtime/Initialization.hpp"

#include "../Sending/LookupResult.hpp"
#include "../Sending/SendMachine.hpp"

#include "../Primitives/PrimitiveDescription.hpp"
#include "../Primitives/PrimitiveTable.hpp"

#include "../Object_Layout/ExecutableMap.hpp"
#include "../Object_Layout/ObjectMap.hpp"
#include "../Object_Layout/SlotIterator.hpp"
#include "../Object_Layout/SlotDescription.hpp"

#include "../Objects/Object.hpp"
#include "../Objects/Context.hpp"
#include "../Objects/Process.hpp"
#include "../Objects/Symbol.hpp"
#include "../Objects/Assignment.hpp"
#include "../Objects/ObjectFactory.hpp"

#include "Bytecodes.hpp"
#include "ProcessCycler.hpp"
#include "ExecutionEngine.hpp"


Interpreter::ExecutionEngine::ExecutionEngine(Objects::ObjectFactory* objectFactory, Sending::SendMachine* sendMachine, Primitives::PrimitiveTable* primitiveTable) {
	this->_objectFactory		= objectFactory;
	this->_processCycler		= new Interpreter::ProcessCycler(); //there isnt any reason to inject process cycler
	this->_sendMachine			= sendMachine;
	this->_primitiveTable		= primitiveTable;
	
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
		
		case Interpreter::Bytecodes::Instructions::VMSend:
			this->doVMSend();
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
	
	Objects::Object* literalObject = this->getActiveContext()->getLiteral(index);
	Objects::Object* resultObject = literalObject->clone(this->_objectFactory->getAllocator());

	this->push(resultObject);
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
	Objects::Object* result = lookupResult._resultObject;
	//TODO : Implement error handler
	

	
	
	if (messageSelector->getSymbolParameters() != result->getParameterCount()) {
		// handle error
		return;
	}

	if (result->hasCode()) {
		this->pushForExecution(result, messageReciever);
	}
	else if (result->getType() == Objects::ObjectType::Assignment) {
		Objects::Assignment* assignment = reinterpret_cast<Objects::Assignment*>(result);
		int index = messageReciever->getObjectMap()->getSlotIndex(assignment->getAssociatedSlot());
		if (index == -1) {
			// handle error
			return;
		}

		Objects::Object* assignedValue = this->pop();
		if (messageReciever->getValue(index)->getParameterCount() != assignedValue->getParameterCount()) {
			// handle error
			return;
		}

		messageReciever->setValue(index, assignedValue);
	}
	else {
	   // data object
		this->push(result);
	}
}
void Interpreter::ExecutionEngine::doVMSend() {
	Objects::Symbol* messageSelector;
	Objects::Object* tmp = this->pop();
	if (tmp->getType() != Objects::ObjectType::Symbol)
		return;
	
	messageSelector = reinterpret_cast<Objects::Symbol*>(tmp);

	Primitives::PrimitiveDescription* desc = this->_primitiveTable->getPrimitive(messageSelector);
	if (desc == nullptr) 
		return; 

	this->pushParameters(desc->getParameterCount());

	
	Objects::Object* result = (desc->getRoutine())(Runtime::_dependencyContainer, this->_parameters);

	this->push(result);
}
void Interpreter::ExecutionEngine::doSendMyself() {
	this->doPushSelf();
	this->doSend();
}

// Methods for executable objects

void Interpreter::ExecutionEngine::pushForExecution(Objects::Object* executableObject, Objects::Object* reciever) {
	Object_Layout::ExecutableMap* execMap = reinterpret_cast<Object_Layout::ExecutableMap*>(executableObject->getObjectMap());
	Object_Layout::ScopeType scopeType = execMap->getScopeType(); 

	// If scope is dynamic , we will use message reciever from doSend
	// If scope is lexical , we will use method from previous context
	Objects::Object* parentLink = (scopeType == Object_Layout::ScopeType::Dynamic) ? (reciever) : (this->getActiveContext()->getReflectee());
	Objects::Object* objectActivation = executableObject->clone(this->_objectFactory->getAllocator());

	objectActivation->setValue(0, parentLink);

	Object_Layout::SlotDescription* activeDesc = nullptr;
	Object_Layout::SlotIterator slotIterator = execMap->getIterator();
	slotIterator.nextItem();

	unsigned char parameterIndex = 0;
	while (not slotIterator.isEnd()) {
		activeDesc = slotIterator.nextItem();
		if (activeDesc->isParameter()) {
			objectActivation->setSlot(
				activeDesc->getName(),
				this->_parameters[parameterIndex]
			);
			parameterIndex++;
		}
	}

	this->getActiveProcess()->pushContext(
		this->_objectFactory->createContext(
			this->getActiveContext(), objectActivation
		)
	);
	
}

bool Interpreter::ExecutionEngine::pushParameters(unsigned short parameterCount) {
	// This method will load objects from process stack and save it into _parameters array
	// If there is not enough parameters , we will return false

	Objects::Object* parameter = nullptr;
	for (unsigned i = 0; i < parameterCount; i++) {
		parameter = this->pop();
		if (parameter == nullptr) {
			return false;
		}
		this->_parameters[31 - i] = parameter;
	}
	return true;
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
