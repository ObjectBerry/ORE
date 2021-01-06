#pragma once

namespace Objects {
	class Object;
	class Process;
}
namespace Interpreter {
	class ProcessCycler {
		unsigned short		_processCount;
		Objects::Process*	_activeProcess;

	public:
		ProcessCycler();

		void addProcess(Objects::Process* process);
		void removeActiveProcess();
		void insertBetween(Objects::Process* process, Objects::Process* prev, Objects::Process* next);

	public:
		inline Objects::Process* getActiveProcess() { return this->_activeProcess; }
		void nextProcess();
		void prevProcess();

		inline bool hasProcesses() { return this->_processCount > 0; }
	};
}
