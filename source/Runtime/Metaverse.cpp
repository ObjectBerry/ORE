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