#pragma once
namespace Memory {
	class MemoryAllocator;
}

namespace Runtime {
	void initializeVM(int argc, char** argv);
}
namespace Runtime {
	class DependencyContainer {
		friend void Runtime::initializeVM(int argc, char** argv);

		Memory::MemoryAllocator* _basicAllocator;
		Memory::MemoryAllocator* _tenuredAllocator;
		Memory::MemoryAllocator* _pernamentAllocator;
	
	public:
		DependencyContainer();

	public:
		Memory::MemoryAllocator* getBasicAllocator()		{ return this->_basicAllocator; };
		Memory::MemoryAllocator* getTenuredAllocator()		{ return this->_tenuredAllocator; };
		Memory::MemoryAllocator* getPernamentAllocator()	{ return this->_tenuredAllocator; };
	
		
	};
}