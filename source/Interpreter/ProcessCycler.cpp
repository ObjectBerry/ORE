#include "../Objects/Process.hpp"

#include "ProcessCycler.hpp"

Interpreter::ProcessCycler::ProcessCycler() {
	this->_processCount = 0;
	this->activeProcess = nullptr;
}

void Interpreter::ProcessCycler::addProcess(Objects::Process* process) {
	// TODO: This can be refactored
	if (this->activeProcess == nullptr) {
		this->activeProcess = process;

		this->activeProcess->setNextProcess(this->activeProcess);
		this->activeProcess->setPrevProcess(this->activeProcess);

		
	}
	else {
		process->setNextProcess(this->activeProcess->getNextProcess());
		this->activeProcess->setNextProcess(process);
	}
	this->_processCount++;
}
void Interpreter::ProcessCycler::removeActiveProcess() {
	if (this->_processCount == 0) {
		return;
	}
	if (this->_processCount == 1) {
		this->activeProcess = nullptr;
		this->_processCount--;
		return;
	}

	Objects::Process* prev, * next;

	prev = this->activeProcess->getPrevProcess();
	next = this->activeProcess->getNextProcess();

	prev->setNextProcess(next);
	next->setPrevProcess(prev);

	this->_processCount--;
}

void Interpreter::ProcessCycler::insertBetween(Objects::Process* process, Objects::Process* prev, Objects::Process* next) {
	process->setPrevProcess(prev);
	process->setNextProcess(next);

	prev->setNextProcess(process);
	next->setPrevProcess(process);
}

void Interpreter::ProcessCycler::nextProcess() {
	this->activeProcess = this->activeProcess->getNextProcess();
}
void Interpreter::ProcessCycler::prevProcess() {
	this->activeProcess = this->activeProcess->getPrevProcess();
}