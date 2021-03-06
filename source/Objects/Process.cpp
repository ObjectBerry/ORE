#include "Context.hpp"
#include "ObjectArray.hpp"

#include "Process.hpp"



Objects::Process::Process(Object_Layout::ObjectMap* objectMap, Objects::ObjectArray* objectStack) : Objects::SlotObject(objectMap) {
	this->_objectStack = objectStack;
	this->_stackTop = 0;

	this->_activeContext = nullptr;
	this->_nextProcess = nullptr;
	this->_prevProcess = nullptr;

	this->clearProcessResult();

	this->_objectType = Objects::ObjectType::Process;
}



Objects::Process* Objects::Process::clone(Memory::MemoryAllocator* allocator) {
	/* Only thing that process clone is object stack
	// Cloned process doesnt have context and links to other process are set to nullptr
	// Reason is simple - if we cloned context too , we will create new branch in cactus stack
	// We would be forced to clone whole context stack.
	// Instead , we will leave this job to user of machine (adding context and adding process to cycler)
	*///
	Objects::Process* clonnedProcess = new(allocator) Objects::Process(this->getObjectMap(), this->_objectStack->clone(allocator));
	clonnedProcess->_stackTop = this->_stackTop;
	clonnedProcess->_activeContext = nullptr; 

	this->_nextProcess = nullptr;
	this->_prevProcess = nullptr;
	
	return clonnedProcess;
}

void Objects::Process::push(Objects::SlotObject* item) {
	this->_objectStack->atPut(this->_stackTop, item);
	this->_stackTop++;
}
Objects::SlotObject* Objects::Process::pop() {
	if (this->_stackTop == 0) {
		return nullptr;
	}
	this->_stackTop--;
	return this->_objectStack->at(this->_stackTop);
}
bool Objects::Process::isStackFull() {
	return this->_stackTop == this->_objectStack->getArrayLength();
}



void Objects::Process::pushContext(Objects::Context* context) {
	context->setPrevious(this->_activeContext);
	this->_activeContext = context;
}

Objects::Context* Objects::Process::popContext() {

	Objects::Context* topContext = this->_activeContext;
	if (topContext == nullptr) {
		return nullptr;
	}
	this->_activeContext = this->_activeContext->getPrevious();
	return topContext;
}

void Objects::Process::clearProcessResult() {
	this->_processResult	= nullptr;
	this->_errorResult		= false;
}
void Objects::Process::setProcessResult(Objects::SlotObject* processResult, bool errorResult) {
	this->_processResult = processResult;
	this->_errorResult	 = errorResult;
}