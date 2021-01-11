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
	Objects::Object* resultObject, * findedObject, * activeObject;
	resultObject = findedObject = activeObject = nullptr; //set them all to nullptr

	// Lookup queue must contain any object to even start lookup
	if (this->_lookupQueue->isEmpty()) {
		return Sending::LookupResult{ nullptr, Sending::LookupState::InvalidInput };
	}

	while (resultObject == nullptr) { 
		while (not this->_lookupQueue->isEmpty()) {
			activeObject = this->_lookupQueue->dequeue();

			if (activeObject->getVisitedObject()) {
				continue;
			}

			//Mark object as visited so we will avoid it in future
			_visitedQueue->enqueue(activeObject); 
			activeObject->setVisitedObject(true); 

			findedObject = activeObject->getSlot(slotName);

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

		if (resultObject != nullptr || this->_parentQueue->isEmpty()) {
			break;
		}
		
		
		while (not this->_parentQueue->isEmpty()) {
			Object_Layout::SlotDescription* activeDescription;
			Objects::Object* lookupedObject = this->_parentQueue->dequeue();
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
		}

		if (this->_lookupQueue->isEmpty())
			break;
	}
	while (not this->_visitedQueue->isEmpty())
		this->_visitedQueue->dequeue()->setVisitedObject(false);
	this->_lookupQueue->resetQueue();
	this->_parentQueue->resetQueue();

	return Sending::LookupResult{
		resultObject,
		resultObject == nullptr ? Sending::LookupState::ZeroResults : Sending::LookupState::OK
	};
}

Sending::LookupResult Sending::SendMachine::sendMessage(Objects::Object* reciever, Objects::Symbol* selector, bool isResend) {
	if (isResend) {
		// TODO: Refactor this into independt method
		Object_Layout::SlotIterator recieverIterator = reciever->getObjectMap()->getIterator();
		Object_Layout::SlotDescription* activeDescription = nullptr;

		
		while (not(recieverIterator.isEnd())) {
			activeDescription = recieverIterator.nextItem();
			if (activeDescription->isParent()) {
				Objects::Object* parentObject = reciever->getSlot(selector);
				this->_lookupQueue->enqueue(
					reciever->getSlot(activeDescription->getName())
				);
			}
		};
	}
	else {
		this->_lookupQueue->enqueue(reciever);
	}

	return this->lookupFor(selector);
}