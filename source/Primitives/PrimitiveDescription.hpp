#pragma once
namespace Runtime {
	class Metaverse; 
}
namespace Objects {
	class SlotObject;
}
namespace Primitives {

	/* This is holder of primitive method 
	// It contains importat info about method - method name , parameter count and pointer to method itself
	*///
	class PrimitiveDescription {
		// name of primitive - we wont use Objects::symbol here 
		const char*		_primitiveName;
		unsigned short	_nameLength;
		unsigned short	_parameterCount;

		Objects::SlotObject* (*_routine)(Runtime::Metaverse* metaverse, Objects::SlotObject** parameters);

	public:
		PrimitiveDescription();
		PrimitiveDescription(const char* primitiveName, unsigned short parameterCount, Objects::SlotObject* (*_routine)(Runtime::Metaverse* metaverse, Objects::SlotObject** parameters));
	
	public:
		inline const char*		getName()			{ return this->_primitiveName; };
		inline unsigned short   getNameLength()		{ return this->_nameLength; };
		inline unsigned short	getParameterCount() { return this->_parameterCount; };

		inline Objects::SlotObject* (*getRoutine())(Runtime::Metaverse* , Objects::SlotObject**) { return this->_routine; };

		bool equalValue(const char* name, unsigned short nameLength);
		inline bool isValid() { return this->_primitiveName != nullptr; };
	};
}