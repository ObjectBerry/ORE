#pragma once
namespace Objects {
	class Object;
	class Process;
}
namespace Interpreter {
	class ProcessCycler {
		unsigned short _processCount;
		Objects::Process* activeProcess;

	public:
		ProcessCycler();

		void createProcess(Objects::Object* method);
		void removeActiveProcess();
		void insertBetween(Objects::Process* process, Objects::Process* prev, Objects::Process* next);

	public:
		inline Objects::Process* getActiveProcess() { return this->activeProcess; }
		void nextProcess();
		void prevProcess();

		inline bool hasProcesses() { return this->_processCount > 0; }
	};
	};
}
