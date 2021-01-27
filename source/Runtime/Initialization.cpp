#include "../Memory/BufferAllocator.hpp"
#include "../Memory/MemoryAllocator.hpp"

#include "../Compiler/ByteTranslator.hpp"

#include "../Object_Layout/MethodMap.hpp"
#include "../Object_Layout/SlotDescription.hpp"
#include "../Object_Layout/SlotType.hpp"

#include "../Objects/Context.hpp"
#include "../Objects/Process.hpp"
#include "../Objects/ObjectArray.hpp"
#include "../Objects/String.hpp"

#include "../Interpreter/ExecutionEngine.hpp"
#include "../Interpreter/ProcessCycler.hpp"

#include "../Primitives/PrimitiveLoader.hpp"
#include "../Sending/SendMachine.hpp"

#include "ObjectUniverse.hpp"
#include "DependencyContainer.hpp"
#include "Initialization.hpp"

namespace Runtime {
	Runtime::DependencyContainer* _dependencyContainer;
}
Runtime::DependencyContainer* Runtime::getDContainer() { return Runtime::_dependencyContainer; };

void Runtime::initializeVM(int argc, char** argv) {
	Runtime::_dependencyContainer = new DependencyContainer();

	// Create allocators (this will be replaced by allocators provided by object memory)
	Runtime::_dependencyContainer->_basicAllocator =		new Memory::BufferAllocator(5120);
	Runtime::_dependencyContainer->_tenuredAllocator =		new Memory::BufferAllocator(2048);
	Runtime::_dependencyContainer->_pernamentAllocator =	new Memory::BufferAllocator(512);

	// Create Object Universe
	Runtime::_dependencyContainer->_objectUniverse = new Runtime::ObjectUniverse(
		Runtime::_dependencyContainer->_basicAllocator,
		Runtime::_dependencyContainer->_tenuredAllocator,
		Runtime::_dependencyContainer->_pernamentAllocator
	);
	Runtime::_dependencyContainer->_objectUniverse->genesis();

	// Create send machine
	Runtime::_dependencyContainer->_sendMachine = new Sending::SendMachine(32,32,32); // we still dont know optimal size for queues
	
	// Create object factory (replaced with object universe)


	// Create table of primitive methods
	Runtime::_dependencyContainer->_primitiveTable = Primitives::initializePrimitiveTable(128); 
	
	// Create Execution engine
	Runtime::_dependencyContainer->_executionEngine = new Interpreter::ExecutionEngine(
		Runtime::_dependencyContainer->_objectUniverse,
		Runtime::_dependencyContainer->_sendMachine,
		Runtime::_dependencyContainer->_primitiveTable
	); 


	Runtime::createBootstrapProcess();
	Runtime::handleLineArguments(argc, argv); 
}

void Runtime::handleLineArguments(int argc, char** argv) {
	Objects::ObjectArray* lineArguments = Runtime::getDContainer()->getObjectUniverse()->createObjectArray(argc); 
	for (unsigned i = 0; i < argc; i++) {
		lineArguments->atPut(i, 
			Runtime::getDContainer()->getObjectUniverse()->createString(argv[i])
		);
	}
}

void Runtime::createBootstrapProcess() {
	// we dont have implemented parsing of basic file yet ... so we will just use precreated bytearray
	char bootstrapBytecode[] = {
			0x00, 0x01, // Number of literals  
			0x00, 0x02, // Number of bytecodes
			0x10, 0x00, 0x00, 0x00, 0x0A, // Literal: SmallInt(10)
			0x10, 0x00,					  // PushLiteral: 0
	};

	Compiler::CodeDescription translatedBootstrap = Compiler::ByteTranslator(
		Runtime::getDContainer()->getObjectUniverse(),
		bootstrapBytecode, 
		sizeof(bootstrapBytecode)
	).translateCode();

	Object_Layout::MethodMap* bootstrapMap = Runtime::getDContainer()->getObjectUniverse()->createMethodMap(0);
	bootstrapMap->setCodeDescription(
		translatedBootstrap._bytecodes,
		translatedBootstrap._literals,
		Object_Layout::ScopeType::Lexical,
		Object_Layout::ReturnType::Normal
	);

	
	Objects::Object* bootstrapMethod = bootstrapMap->constructObject(Runtime::getDContainer()->getObjectUniverse()->getAllocator());
	bootstrapMethod->setValue(0, Runtime::getDContainer()->getObjectUniverse()->getLobbyObject());
	//bootstrapMethod->setValue(1, Runtime::handleLineArguments());
	
	
}



void Runtime::start() {
	Runtime::_dependencyContainer->getExecutionEngine()->start();
}
