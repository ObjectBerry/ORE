#include "Routines/ObjectPrimitives.hpp"
#include "Routines/IntegerPrimitives.hpp"

#include "PrimitiveDescription.hpp"
#include "PrimitiveTable.hpp"
#include "PrimitiveLoader.hpp"


Primitives::PrimitiveTable* Primitives::initializePrimitiveTable(unsigned short length) {
	Primitives::_table = new Primitives::PrimitiveTable(length);
	Primitives::loadPrimitives();
	return Primitives::_table;
}

void Primitives::loadPrimitive(const char* name, unsigned short parameterCount, Objects::Object* (*routine)(Runtime::Metaverse*, Objects::Object**)) {
	Primitives::_table->addPrimitive(Primitives::PrimitiveDescription(
		name,
		parameterCount,
		routine
	));
}

void Primitives::loadPrimitives() {
	//Object primitives
	loadPrimitive("clone",		1, Primitives::clone);
	loadPrimitive("identity",	2, Primitives::clone);

	//Integer primitives
	loadPrimitive("addSmi", 2, Primitives::addSmi);
	loadPrimitive("subSmi", 2, Primitives::subSmi);
	loadPrimitive("mulSmi", 2, Primitives::mulSmi);
	loadPrimitive("divSmi", 2, Primitives::divSmi); 

}