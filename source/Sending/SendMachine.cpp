#include "../Object_Layout/ObjectMap.hpp"
#include "../Object_Layout/SlotIterator.hpp"
#include "../Object_Layout/SlotDescription.hpp"
#include "../Objects/Symbol.hpp"

#include "ObjectQueue.hpp"
#include "LookupResult.hpp"
#include "SendMachine.hpp"

Sending::SendMachine::SendMachine(unsigned char parentQueueSize, unsigned char lookupQueueSize, unsigned char visitedQueueSize) {
	this->visitedQueue = new ObjectQueue(visitedQueueSize);
	this->lookupQueue = new ObjectQueue(lookupQueueSize);
	this->parentQueue = new ObjectQueue(parentQueueSize);
}

Sending::LookupResult Sending::SendMachine::sendMessage(Objects::Object* reciever, Objects::Symbol* selector, bool isResend) {
	if (isResend) {
		// TODO: Refactor this into independt method
		Object_Layout::SlotIterator recieverIterator = reciever->getObjectMap()->getIterator();
		Object_Layout::SlotDescription* activeDescription = nullptr;

		
		while (not(recieverIterator.isEnd())) {
			activeDescription = recieverIterator.nextItem();
			if (activeDescription->isParent()) {
				this->lookupQueue->enqueue(
					reciever->getSlot(selector)
				);
			}
		};
	}
	else {
		this->lookupQueue->enqueue(reciever);
	}


}