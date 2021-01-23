#pragma once
namespace Primitives {
	class PrimitiveTable;
	class PrimitiveDescription;
}

namespace Primitives {
	namespace {
		Primitives::PrimitiveTable* _table;
	}
	Primitives::PrimitiveTable* initializePrimitiveTable(unsigned short length);
	
	Primitives::PrimitiveDescription loadPrimitive(const char* name, unsigned short parameterCount, Objects::Object* (*routine)(Runtime::DependencyContainer*, Objects::Object**));
	void loadPrimitives();
	
}