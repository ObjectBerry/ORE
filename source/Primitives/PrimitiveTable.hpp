#pragma once
namespace Objects {
	class Symbol;
	enum class SymbolType : unsigned short;
}
namespace Primitives {
	class PrimitiveDescription;
}

namespace Primitives {

	/* Primitive table is hash table used to store primitive methods 
	// It is implemented as simple array that will increase index during invalid position
	*///
	class PrimitiveTable {
		Primitives::PrimitiveDescription*	_storage;
		unsigned short						_length;
		unsigned short						_count;

		
	public:
		PrimitiveTable(unsigned short length);
		
	private:
		unsigned int hashSymbol(const char* characters, unsigned short length, Objects::SymbolType symbolType, unsigned short parameterCount);

	public:

		void addPrimitive(Primitives::PrimitiveDescription primitiveDescription);
		Primitives::PrimitiveDescription* getPrimitive(Objects::Symbol* symbol);
	};
}