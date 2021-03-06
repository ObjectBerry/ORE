

#include "../Objects/SlotObject.hpp"

#include "ObjectQueue.hpp"
Sending::ObjectQueue::ObjectQueue( unsigned short queueLength) {
	this->_queueLength	= queueLength;
	this->_storage		= new Objects::SlotObject * [queueLength];
	this->resetQueue();
}
Sending::ObjectQueue::~ObjectQueue() {
	delete[] this->_storage;
}

void Sending::ObjectQueue::enqueue(Objects::SlotObject* item) {
	this->_storage[this->_first] = item;
	this->_first = (this->_first + 1) % this->_queueLength;
}
Objects::SlotObject* Sending::ObjectQueue::dequeue() {
	if (this->isEmpty()) {
		return nullptr;
	}
	Objects::SlotObject* item = this->_storage[this->_last];
	this->_last = (this->_last + 1) % this->_queueLength;
	
	return item;
}



void Sending::ObjectQueue::resetQueue() {
	this->_first	= 0;
	this->_last		= 0;

}