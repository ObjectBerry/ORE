#pragma once
namespace Runtime {
	class Metaverse; 
}
namespace Objects {
	class Object;
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

		Objects::Object* (*_routine)(Runtime::Metaverse* metaverse, Objects::Object** parameters);

	public:
		PrimitiveDescription();
		PrimitiveDescription(const char* primitiveName, unsigned short parameterCount, Objects::Object* (*_routine)(Runtime::Metaverse* metaverse, Objects::Object** parameters));
	
	public:
		inline const char*		getName()			{ return this->_primitiveName; };
		inline unsigned short   getNameLength()		{ return this->_nameLength; };
		inline unsigned short	getParameterCount() { return this->_parameterCount; };

		inline Objects::Object* (*getRoutine())(Runtime::Metaverse* , Objects::Object**) { return this->_routine; };

		bool equalValue(const char* name, unsigned short nameLength);
		inline bool isValid() { return this->_primitiveName != nullptr; };
	};
}