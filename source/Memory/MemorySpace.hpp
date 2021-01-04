#pragma once

namespace Memory {
	class MemorySpace {
		unsigned short _bufferSize;
		char* _buffer;
		char* _bufferForwardPointer;
		char* _bufferBackwardPointer;

		MemorySpace* _nextSpace;
		MemorySpace* _prevSpace;
	public:
		MemorySpace(unsigned short bufferSize);
		~MemorySpace();

	public:
		void    resetBuffer();
		bool	isLimit(size_t size);
		void*	allocateMemory(size_t size, bool fromEnd = false);

	public:
		inline MemorySpace* getNext()					{ return this->_nextSpace; }
		inline void			setNext(MemorySpace* next)	{ this->_nextSpace = next; };
		inline MemorySpace* getPrev()					{ return this->_prevSpace; }
		inline void			setPrev(MemorySpace* prev)	{ this->_prevSpace = prev; };

		inline char*			getBuffer() { return this->_buffer; };
		inline unsigned short	getBufferSize() { return this->_bufferSize; };
	};
}