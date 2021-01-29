#include "../Objects/Process.hpp"

#include "ProcessCycler.hpp"

Interpreter::ProcessCycler::ProcessCycler() {
	this->_processCount = 0;
	this->_activeProcess = nullptr;
}

void Interpreter::ProcessCycler::addProcess(Objects::Process* process) {
	// TODO: This can be refactored
	if (this->_activeProcess == nullptr) {
		this->_activeProcess = process;

		this->_activeProcess->setNextProcess(this->_activeProcess);
		this->_activeProcess->setPrevProcess(this->_activeProcess);

		
	}
	else {
		process->setNextProcess(this->_activeProcess->getNextProcess());
		this->_activeProcess->setNextProcess(process);
	}
	this->_processCount++;
}
Objects::Process* Interpreter::ProcessCycler::removeActiveProcess() {
	if (this->_processCount == 0) {
		return nullptr;
	}
	
	Objects::Process* resultProcess = nullptr;
	if (this->_processCount == 1) {
		resultProcess = this->_activeProcess;
		
		this->_activeProcess = nullptr;
		this->_processCount--;
		
		return resultProcess;
	}

	Objects::Process* prev, * next;

	prev = this->_activeProcess->getPrevProcess();
	next = this->_activeProcess->getNextProcess();

	prev->setNextProcess(next);
	next->setPrevProcess(prev);
	
	resultProcess = this->_activeProcess;
	this->_activeProcess = next;

	this->_processCount--;

	return resultProcess;
}

void Interpreter::ProcessCycler::insertBetween(Objects::Process* process, Objects::Process* prev, Objects::Process* next) {
	process->setPrevProcess(prev);
	process->setNextProcess(next);

	prev->setNextProcess(process);
	next->setPrevProcess(process);
}

void Interpreter::ProcessCycler::nextProcess() {
	this->_activeProcess = this->_activeProcess->getNextProcess();
}
void Interpreter::ProcessCycler::prevProcess() {
	this->_activeProcess = this->_activeProcess->getPrevProcess();
}