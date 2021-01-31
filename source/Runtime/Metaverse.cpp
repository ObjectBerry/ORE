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
#include "Metaverse.hpp"

Runtime::Metaverse::Metaverse() {
	this->initialized = false;

	this->_basicAllocator		= nullptr;
	this->_tenuredAllocator		= nullptr;
	this->_pernamentAllocator	= nullptr;

	this->_objectUniverse	= nullptr;
	this->_sendMachine		= nullptr;
	this->_primitiveTable	= nullptr;
	this->_executionEngine	= nullptr;
}

Runtime::Metaverse* Runtime::Metaverse::create() {
	Runtime::Metaverse* newMetaverse = new Runtime::Metaverse();

	// Create allocators (this will be replaced by allocators provided by object memory)
	newMetaverse->_basicAllocator = new Memory::BufferAllocator(5120);
	newMetaverse->_tenuredAllocator = new Memory::BufferAllocator(2048);
	newMetaverse->_pernamentAllocator = new Memory::BufferAllocator(512);

	// Create Object Universe
	newMetaverse->_objectUniverse = new Runtime::ObjectUniverse(
		newMetaverse
	);
	newMetaverse->_objectUniverse->genesis();

	// Create send machine
	newMetaverse->_sendMachine = new Sending::SendMachine(32, 32, 32); // we still dont know optimal size for queues

	// Create object factory (replaced with object universe)


	// Create table of primitive methods
	newMetaverse->_primitiveTable = Primitives::initializePrimitiveTable(128);

	// Create Execution engine
	newMetaverse->_executionEngine = new Interpreter::ExecutionEngine(
		newMetaverse
	);
	
	newMetaverse->initialized = true; 
	return newMetaverse; 
}

void Runtime::Metaverse::initialize(int argCount, char** arguments) {
	Compiler::CodeDescription bootstrapCode = this->readBoostrap(); 

	Objects::ObjectArray* argumentArray = this->handleArguments(argCount, arguments);
	this->_objectUniverse->initializeBootstrap(bootstrapCode, argumentArray);

}

void Runtime::Metaverse::start() {
	this->getExecutionEngine()->getProcessCycler()->addProcess(
		this->getObjectUniverse()->createProcess(16)
	);
	this->_executionEngine->pushForExecution(this->_objectUniverse->getBootstrapMethod(), this->_objectUniverse->getLobbyObject());
	this->_executionEngine->start();
}

Objects::ObjectArray* Runtime::Metaverse::handleArguments(int argCount, char** arguments) {
	Objects::ObjectArray* argumentArray = this->getObjectUniverse()->createObjectArray(argCount); 
	for (unsigned i = 0; i < argCount; i++) {
		argumentArray->atPut(i,
			this->getObjectUniverse()->createString(arguments[i])
		);
	}
	return argumentArray; 
}

Compiler::CodeDescription Runtime::Metaverse::readBoostrap() {
	/*
	This should be refactored into own prototypical object that is allocated using 
	*/
	
	FILE* bootstrapFile = fopen("P:\\ORE\\ORE\\Debug\\bootstrap.ore", "rb");

	char fileHeader[5];
	fread(fileHeader, 5, 1, bootstrapFile);
	const char magicString[] = "ORE";
	for (unsigned i = 0; i < 3; i++) {
		if (fileHeader[i] != magicString[i])
			throw 1;
	}
	
	unsigned short codeLength = 0;
	codeLength += fileHeader[3];
	codeLength <<= 8;
	codeLength += fileHeader[4];

	char* fileCode = this->_basicAllocator->allocateBytes(codeLength);
	
	fread(fileCode, codeLength, 1, bootstrapFile);
	fclose(bootstrapFile);

	return Compiler::ByteTranslator(this->getObjectUniverse(), fileCode, codeLength).translateCode();

	
}