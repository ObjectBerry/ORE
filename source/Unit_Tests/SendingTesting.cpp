#include "../Memory/BufferAllocator.hpp"
#include "../Sending/ObjectQueue.hpp"
#include "../Objects/Object.hpp"

#include "SendingTesting.hpp"

Unit_Tests::SendingTesting::SendingTesting() : Unit_Tests::TestCase("Sending Tests") {};

void Unit_Tests::SendingTesting::runTests() {
	Memory::BufferAllocator* allocator = new Memory::BufferAllocator(1000);
	Sending::ObjectQueue objectQueue(4);

	Objects::Object *first, *second, *third;
	first = Objects::Object::createWithMap(allocator,1);
	second = first->clone(allocator);
	third = second->clone(allocator);

	DO_CHECK("Object queue: check of emptyness 1", objectQueue.isEmpty());
	objectQueue.enqueue(first);
	DO_CHECK("Object queue: check of emptyness 2", objectQueue.isEmpty() == false);

	objectQueue.enqueue(second);
	objectQueue.enqueue(third);

	DO_CHECK("Object queue: dequeue 1", objectQueue.dequeue() == first);
	DO_CHECK("Object queue: dequeue 2", objectQueue.dequeue() == second);
	DO_CHECK("Object queue: dequeue 3", objectQueue.dequeue() == third); 
	// Testing queue circularity 

	objectQueue.enqueue(first);
	objectQueue.enqueue(second);
	objectQueue.dequeue(); 
	
	DO_CHECK("Object queue: circularity test", objectQueue.dequeue() == second);  

	delete allocator; 
}