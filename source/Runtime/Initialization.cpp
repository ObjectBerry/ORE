#include "../Memory/MemoryAllocator.hpp"

#include "../Interpreter/ExecutionEngine.hpp"

#include "DependencyContainer.hpp"
#include "Initialization.hpp"

void Runtime::initializeVM(int argc, char** argv) {
	Runtime::_dependencyContainer = new DependencyContainer();

	Runtime::_dependencyContainer->_basicAllocator;
}
void Runtime::handleLineArguments(int argc, char** argv) {

}

void Runtime::parseResourceFile() {

}
