#include "../Memory/BufferAllocator.hpp"
#include "../Memory/MemoryAllocator.hpp"

#include "../Objects/String.hpp"

#include "../Interpreter/ExecutionEngine.hpp"
#include "../Interpreter/ProcessCycler.hpp"

#include "../Primitives/PrimitiveLoader.hpp"
#include "../Objects/ObjectFactory.hpp"
#include "../Sending/SendMachine.hpp"

#include "DependencyContainer.hpp"
#include "Initialization.hpp"

void Runtime::initializeVM(int argc, char** argv) {
	Runtime::_dependencyContainer = new DependencyContainer();

	Runtime::_dependencyContainer->_basicAllocator =		new Memory::BufferAllocator(1024);
	Runtime::_dependencyContainer->_tenuredAllocator =		new Memory::BufferAllocator(1024);
	Runtime::_dependencyContainer->_pernamentAllocator =	new Memory::BufferAllocator(1024);

	Runtime::_dependencyContainer->_sendMachine = new Sending::SendMachine(32,32,32); // we still dont know optimal size for queues
	Runtime::_dependencyContainer->_objectFactory = new Objects::ObjectFactory(
		Runtime::_dependencyContainer->_basicAllocator,
		Runtime::_dependencyContainer->_pernamentAllocator
	);
	Runtime::_dependencyContainer->_primitiveTable = Primitives::initializePrimitiveTable(128); 
	Runtime::_dependencyContainer->_executionEngine = new Interpreter::ExecutionEngine(
		Runtime::_dependencyContainer->_objectFactory,
		Runtime::_dependencyContainer->_sendMachine,
		Runtime::_dependencyContainer->_primitiveTable
	); 


	Runtime::parseResourceFile();
}
void Runtime::handleLineArguments(int argc, char** argv) {
	for (unsigned i = 0; i < argc; i++) {
		Runtime::_dependencyContainer->getExecutionEngine()->push(
			 Runtime::_dependencyContainer->getObjectFactory()->createString(argv[i])
		);
	}
}

void Runtime::parseResourceFile() {

}



void Runtime::start() {
	Runtime::_dependencyContainer->getExecutionEngine()->start();
}
