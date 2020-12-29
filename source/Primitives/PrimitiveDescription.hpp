#pragma once
namespace Objects {
	class Object;
	enum class SymbolType : unsigned short;
}

namespace Primitives {
	class PrimitiveDescription {
		// name of primitive
		// we dont use Objects::Symbol here because we dont want include primitive methods into garbage collection
		// it will be little slower , but it is acceptable
		// + every primitive is alphanumerical , so we will save 2 bytes
		const char*			_primitiveName;
		unsigned short		_parameterCount;

		// hash of primitive name
		unsigned int		_hash;
		void calculateHash();
	
		// pointer to primitive method
		Objects::Object*	(*_routine)(Objects::Object** arguments);
	
	
	public:
		PrimitiveDescription(const char* _primitiveName, unsigned short _parameterCount, Objects::Object* (*_getRoutine())(Objects::Object**));

	public:
		bool equalName(Objects::Symbol* comparedName);

		inline Objects::Object* (*getRoutine())(Objects::Object**) { return this->_routine; };
		inline unsigned short getParameterCount() { return this->_parameterCount; }
	};
}