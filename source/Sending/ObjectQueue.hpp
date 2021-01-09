#pragma once

namespace Objects {
	class Object;
}

namespace Sending {
	class ObjectQueue {
		
		unsigned short		_queueLength;
		Objects::Object**	_storage;
		unsigned short		_first;
		unsigned short		_last;

	public:
		ObjectQueue(unsigned short queueLength);
		~ObjectQueue();

	public:
		void				enqueue(Objects::Object* item);
		Objects::Object*	dequeue();

		void				resetQueue();
		inline bool			isEmpty() { return this->_first == this->_last; };
		
	};
}