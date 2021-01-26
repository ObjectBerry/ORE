#include "../Object_Layout/ObjectMap.hpp"
#include "../Object_Layout/SlotIterator.hpp"
#include "../Object_Layout/SlotDescription.hpp"
#include "../Objects/Symbol.hpp"

#include "ObjectQueue.hpp"
#include "LookupResult.hpp"
#include "SendMachine.hpp"

Sending::SendMachine::SendMachine(unsigned char parentQueueSize, unsigned char lookupQueueSize, unsigned char visitedQueueSize) {
	this->_visitedQueue = new ObjectQueue(visitedQueueSize);
	this->_lookupQueue = new ObjectQueue(lookupQueueSize);
	this->_parentQueue = new ObjectQueue(parentQueueSize);
}

Sending::SendMachine::~SendMachine() {
	delete this->_visitedQueue;
	delete this->_lookupQueue;
	delete this->_parentQueue;
}


Sending::LookupResult Sending::SendMachine::lookupFor(Objects::Symbol* slotName) {
	// Lookuping method of send machine
	// It is using breadth-first search to travel graph (objects are nodes of graph , slot's links are edges of graph)
	// Every object is chcecked only once during traveling

	// Create variables used during traveling and set them to nullptr
	Objects::Object* resultObject, * findedObject, * activeObject;
	resultObject = findedObject = activeObject = nullptr;

	//
	while (resultObject == nullptr) { 
		while (not this->_lookupQueue->isEmpty()) {
			activeObject = this->_lookupQueue->dequeue();

			// Avoid alredy visited objects
			if (activeObject->getVisitedObject())
				continue;
			

			//Mark object as visited so we will avoid it in future
			_visitedQueue->enqueue(activeObject); 
			activeObject->setVisitedObject(true); 

			findedObject = activeObject->getSlot(slotName);

			// Now we will decide what to do next after we searched object for slot we want
			// If we found something (findedObject is not nullptr) we will continue
			// BUT if we found slot before , we will return invalid result - there cant be two slots with same name in one generation 
			if (findedObject != nullptr) {
				if (resultObject != nullptr) {
					//todo: refactor this
					while (not this->_visitedQueue->isEmpty()) {
						this->_visitedQueue->dequeue()->setVisitedObject(false);
					}
					return Sending::LookupResult{ nullptr, Sending::LookupState::MultipleResults };
				}
				resultObject = findedObject;
				continue;
			}

			this->_parentQueue->enqueue(activeObject);
		}

		this->_lookupQueue->resetQueue();

		// If we found our slot or if we traveled whole graph we will break from loop
		// (parentQueue is holding parent object - if it is empty , that means we traveled all objects)
		if (resultObject != nullptr || this->_parentQueue->isEmpty()) 
			break;
		
		// This will add all parent objects into next search
		// Explanation is in addParentFrom method
		while (not this->_parentQueue->isEmpty()) 
			this->addParentsFrom(this->_parentQueue->dequeue());

		if (this->_lookupQueue->isEmpty())
			break;
	}

	// Empty queues - after finished traversal , we dont need their content anymore
	// During empting of visitedQueue , we will set all objects 'visited' to false
	while (not this->_visitedQueue->isEmpty())
		this->_visitedQueue->dequeue()->setVisitedObject(false);
	this->_lookupQueue->resetQueue();
	this->_parentQueue->resetQueue();

	return Sending::LookupResult{
		resultObject,
		resultObject == nullptr ? Sending::LookupState::ZeroResults : Sending::LookupState::OK
	};
}


void Sending::SendMachine::addParentsFrom(Objects::Object* lookupedObject) {
	// This method will take object and it will iterate through slots
	// If it found any parent slot , it will load object from that slot and add it into lookup
	
	Object_Layout::SlotDescription* activeDescription;
	Object_Layout::SlotIterator lookupedIterator = lookupedObject->getObjectMap()->getIterator();
	
	while (not lookupedIterator.isEnd()) {
		activeDescription = lookupedIterator.nextItem();
		if (activeDescription->isParent()) {
			this->_lookupQueue->enqueue(
				lookupedObject->getSlot(
					activeDescription->getName()
				)
			);
		}
	}
};


Sending::LookupResult Sending::SendMachine::sendMessage(Objects::Object* reciever, Objects::Symbol* selector, bool isResend) {
	// Main method and only public method (+ constructor/destructor) in SendMachine
	// This is just proxy to lookup mechanism that is getting all parameters that we need to start lookup
	// Thanks to refactoring it is very smal

	if (isResend) {
		this->addParentsFrom(reciever);
	}
	else {
		this->_lookupQueue->enqueue(reciever);
	}

	return this->lookupFor(selector);
}