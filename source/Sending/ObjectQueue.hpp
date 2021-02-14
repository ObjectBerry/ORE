#pragma once

namespace Objects {
	class SlotObject;
}

namespace Sending {

	/* ObjectQueue is implementation of FIFO structure 
	// It is using preallocated array instead of linked list - it will improve memory requests
	*/
	class ObjectQueue {
		
		unsigned short		_queueLength;
		Objects::SlotObject**	_storage;
		unsigned short		_first;
		unsigned short		_last;

	public:
		ObjectQueue(unsigned short queueLength);
		~ObjectQueue();

	public:
		void				enqueue(Objects::SlotObject* item);
		Objects::SlotObject*	dequeue();

		void				resetQueue();
		inline bool			isEmpty() { return this->_first == this->_last; };
		
	};
}