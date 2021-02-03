#include "../Memory/BufferAllocator.hpp"

#include "../Object_Layout/ObjectMap.hpp"
#include "../Objects/ObjectArray.hpp"
#include "../Objects/Process.hpp"

#include "../Interpreter/ProcessCycler.hpp"

#include "InterpreterTesting.hpp"

Unit_Tests::InterpreterTesting::InterpreterTesting() : Unit_Tests::TestCase("Interpreter tests") {};

void Unit_Tests::InterpreterTesting::runTests() {
	Interpreter::ProcessCycler* cycler = new Interpreter::ProcessCycler();
	Memory::BufferAllocator* allocator = new Memory::BufferAllocator(1000);
	Object_Layout::ObjectMap* objMap = new(allocator) Object_Layout::ObjectMap(1);
	


	Objects::Process* firstProcess = new(allocator)Objects::Process( objMap, nullptr);
	Objects::Process* secondProcess = new(allocator) Objects::Process( objMap, nullptr);
	Objects::Process* thirdProcess = new(allocator) Objects::Process( objMap, nullptr);
	Objects::Process* fourthProcess = new(allocator) Objects::Process( objMap, nullptr);

	cycler->addProcess(firstProcess);
	cycler->addProcess(secondProcess); 


	DO_CHECK("Cycler: list cycling 1 ", cycler->getActiveProcess() == firstProcess);
	cycler->nextProcess();
	DO_CHECK("Cycler: list cycling 2 ", cycler->getActiveProcess() == secondProcess);
	cycler->nextProcess();
	DO_CHECK("Cycler: list cycling 3 ", cycler->getActiveProcess() == firstProcess);

	
	cycler->addProcess(thirdProcess);
	cycler->nextProcess();
	DO_CHECK("Cycler: process insertion 1 ", cycler->getActiveProcess() == thirdProcess); 

	cycler->insertBetween(fourthProcess, firstProcess, thirdProcess);
	cycler->prevProcess();
	DO_CHECK("Cycler: process insertion 2 ", cycler->getActiveProcess() == fourthProcess); 


	cycler->removeActiveProcess();
	DO_CHECK("Cycler: process removing 1", cycler->getActiveProcess() == thirdProcess); 

	while (cycler->hasProcesses()) {
		cycler->removeActiveProcess();
	}
	cycler->addProcess(firstProcess);
	DO_CHECK("Cycler: process removing 2", cycler->getActiveProcess() == firstProcess);
	cycler->nextProcess();
	DO_CHECK("Cycler: process removing 3", cycler->getActiveProcess() == firstProcess);



	delete allocator;
	delete cycler;
}