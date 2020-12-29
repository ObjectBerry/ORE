#pragma once
#include "PrimitiveDescription.hpp"


namespace Primitives {
	
	class PrimitiveTable {
		static const unsigned short _numberOfPrimitives = 10;
		Primitives::PrimitiveDescription _table[PrimitiveTable::_numberOfPrimitives];

	public:
		void addDescription(Primitives::PrimitiveDescription primitiveDescription);
		Primitives::PrimitiveDescription* getDescription()
	};
}