

#include "../Objects/Object.hpp"

#include "ObjectQueue.hpp"

Sending::ObjectQueue::ObjectQueue( unsigned short queueLength) {
	this->_queueLength	= queueLength;
	this->_storage		= new Objects::Object * [queueLength];
	this->resetQueue();
}


void Sending::ObjectQueue::enqueue(Objects::Object* item) {
	this->_storage[this->_first] = item;
	this->_first = (this->_first + 1) % this->_queueLength;
}
Objects::Object* Sending::ObjectQueue::dequeue() {
	if (this->isEmpty()) {
		return nullptr;
	}
	Objects::Object* item = this->_storage[this->_last];
	this->_last++;
	
	return item;
}



void Sending::ObjectQueue::resetQueue() {
	this->_first	= 0;
	this->_last		= 0;

}