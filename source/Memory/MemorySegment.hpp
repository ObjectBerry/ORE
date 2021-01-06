#pragma once

namespace Memory {
	class MemorySegment {
		unsigned short _bufferSize;
		char* _buffer;
		char* _bufferForwardPointer;
		char* _bufferBackwardPointer;

		MemorySegment* _nextSpace;
		MemorySegment* _prevSpace;
	public:
		MemorySegment(unsigned short bufferSize);
		~MemorySegment();

	public:
		void    resetBuffer();
		bool	isLimit(size_t size);
		void*	allocateMemory(size_t size, bool fromEnd = false);

	public:
		inline MemorySegment* getNext()					{ return this->_nextSpace; }
		inline void			setNext(MemorySegment* next)	{ this->_nextSpace = next; };
		inline MemorySegment* getPrev()					{ return this->_prevSpace; }
		inline void			setPrev(MemorySegment* prev)	{ this->_prevSpace = prev; };

		inline char*			getBuffer() { return this->_buffer; };
		inline unsigned short	getBufferSize() { return this->_bufferSize; };
	};
}