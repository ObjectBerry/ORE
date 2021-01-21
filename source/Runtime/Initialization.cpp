#include "../Memory/BufferAllocator.hpp"
#include "../Memory/MemoryAllocator.hpp"

#include "../Interpreter/ExecutionEngine.hpp"

#include "DependencyContainer.hpp"
#include "Initialization.hpp"

void Runtime::initializeVM(int argc, char** argv) {
	Runtime::_dependencyContainer = new DependencyContainer();

	Runtime::_dependencyContainer->_basicAllocator =		new Memory::BufferAllocator(1024);
	Runtime::_dependencyContainer->_tenuredAllocator =		new Memory::BufferAllocator(1024);
	Runtime::_dependencyContainer->_pernamentAllocator =	new Memory::BufferAllocator(1024);
}
void Runtime::handleLineArguments(int argc, char** argv) {

}

void Runtime::parseResourceFile() {

}
