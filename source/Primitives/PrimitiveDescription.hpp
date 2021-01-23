#pragma once
namespace Runtime {
	class DependencyContainer;
}
namespace Objects {
	class Object;
}
namespace Primitives {
	class PrimitiveDescription {
		// name of primitive - we wont use Objects::symbol here 
		const char*		_primitiveName;
		unsigned short	_nameLength;
		unsigned short	_parameterCount;

		Objects::Object* (*_routine)(Runtime::DependencyContainer* dc ,Objects::Object** parameters);

	public:
		PrimitiveDescription();
		PrimitiveDescription(const char* primitiveName, unsigned short parameterCount, Objects::Object* (*_routine)(Runtime::DependencyContainer* dc, Objects::Object** parameters));
	
	public:
		inline const char*		getName()			{ return this->_primitiveName; };
		inline unsigned short   getNameLength()		{ return this->_nameLength; };
		inline unsigned short	getParameterCount() { return this->_parameterCount; };

		inline Objects::Object* (*getRoutine())(Runtime::DependencyContainer*, Objects::Object**) { return this->_routine; };

		bool equalValue(const char* name, unsigned short nameLength);
		inline bool isValid() { return this->_primitiveName != nullptr; };
	};
}