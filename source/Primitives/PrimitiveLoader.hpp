#pragma once
namespace Primitives {
	class PrimitiveTable;
	class PrimitiveDescription;
}
namespace Runtime {
	class DependencyContainer;
}

namespace Primitives {
	namespace {
		Primitives::PrimitiveTable* _table;
	}
	Primitives::PrimitiveTable* initializePrimitiveTable(unsigned short length);
	
	void loadPrimitive(const char* name, unsigned short parameterCount, Objects::Object* (*routine)(Runtime::DependencyContainer*, Objects::Object**));
	void loadPrimitives();
	
}