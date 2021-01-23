#pragma once
namespace Primitives {
	class PrimitiveTable;
	class PrimitiveDescription;
}

namespace Primitives {
	Primitives::PrimitiveTable* initializePrimitiveTable(unsigned short length);
	void loadPrimitives(Primitives::PrimitiveTable* primitiveTable);

}