#include "ByteArray.hpp"
#include "ObjectArray.hpp"

#include "Code.hpp"

Objects::Code::Code(basicParameter, Objects::ByteArray* bytecode, Objects::ObjectArray* literals) : Objects::Object(memoryAllocator,objectMap){
	this->_bytecode = bytecode;
	this->_literals = literals;
}
Objects::Code* Objects::Code::create(basicParameter, Objects::ByteArray* bytecode, Objects::ObjectArray* literals) {
	return new(memoryAllocator) Objects::Code(memoryAllocator, objectMap, bytecode, literals);
}
Objects::Code* Objects::Code::clone(Memory::MemoryAllocator* allocator) {
	return Objects::Code::create(
		allocator,
		this->getObjectMap(),
		this->_bytecode->clone(allocator),
		this->_literals->clone(allocator)
	);
}