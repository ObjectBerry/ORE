#include <stdio.h>

#pragma warning(disable: 4996) 

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
	//Runtime::handleLineArguments(argc, argv); 
}

void Runtime::handleLineArguments(int argc, char** argv) {
	Objects::ObjectArray* lineArguments = Runtime::getDContainer()->getObjectUniverse()->createObjectArray(argc); 
	for (unsigned i = 0; i < argc; i++) {
		lineArguments->atPut(i, 
			Runtime::getDContainer()->getObjectUniverse()->createString(argv[i])
		);
	}
}

char* Runtime::readBootstrapFile() {
	// refactor this in future

	FILE* sourceFile;
	sourceFile = fopen("P:\\ORE\\ORE\\Debug\\bootstrap.ore", "rb");  // r for read, b for binary

	char header[5];
	fread(header, 5, 1, sourceFile);

	//Add checking for ore signature
	const char* oreHead = "ORE";
	for (unsigned i = 0; i < 3; i++) {
		if (oreHead[i] != header[i])
			return nullptr;
	
	}

	unsigned short fileLength = 0;
	fileLength += header[3];
	fileLength <<= 8;
	fileLength += header[4];

	char* result = new char[fileLength + 2];
	result[0] = header[3];
	result[1] = header[4]; 

	char* bootstrapBytecode = (result + 2);
	fread(bootstrapBytecode, fileLength, 1, sourceFile);

	return result;
}

void Runtime::createBootstrapProcess() {
	// we dont have implemented parsing of basic file yet ... so we will just use precreated bytearray
	char* bootstrapBytecode = Runtime::readBootstrapFile();
	/*
	{
			0x00, 0x03, // Number of literals  
			0x00, 0x07, // Number of bytecodes
			0xA1, 0xAA, 0x00, 0x02, 'm', 'u', 'l', 'S', 'm', 'i', 0x00, // Literal: Symbol("addSmi")
			0x10, 0xFF, 0xFF, 0xFF, 0xFF, // Literal: SmallInt(5)
			0x10, 0xFF, 0xFF, 0xFF, 0xFF, // Literal: SmallInt(10)
			
			0x10, 0x01, // PushLiteral: 1
			0x10, 0x02, // PushLiteral: 2
			0x10, 0x00, // PushLiteral: 0
			0x21, // VMSend:
	};
	*/
	unsigned short length = 0;
	length += bootstrapBytecode[0];
	length <<= 8;
	length += bootstrapBytecode[1];


	Compiler::CodeDescription translatedBootstrap = Compiler::ByteTranslator(
		Runtime::getDContainer()->getObjectUniverse(),
		bootstrapBytecode, 
		length
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
	
	Runtime::getDContainer()->getExecutionEngine()->getProcessCycler()->addProcess(
		Runtime::getDContainer()->getObjectUniverse()->createProcess(32, bootstrapMethod)
	);

	delete bootstrapBytecode;
	
}



void Runtime::start() {
	Runtime::_dependencyContainer->getExecutionEngine()->start();
}
