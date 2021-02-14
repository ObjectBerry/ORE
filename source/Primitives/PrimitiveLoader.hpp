#pragma once
namespace Primitives {
	class PrimitiveTable;
	class PrimitiveDescription;
}
namespace Runtime {
	class Metaverse;
}

namespace Primitives {
	namespace {
		Primitives::PrimitiveTable* _table;
	}
	Primitives::PrimitiveTable* initializePrimitiveTable(unsigned short length);
	
	void loadPrimitive(const char* name, unsigned short parameterCount, Objects::SlotObject* (*routine)(Runtime::Metaverse*, Objects::SlotObject**));
	void loadPrimitives();
	
}