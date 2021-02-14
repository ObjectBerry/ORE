#include "Routines/ArrayPrimitives.hpp"
#include "Routines/IntegerPrimitives.hpp"
#include "Routines/MirrorPrimitives.hpp"
#include "Routines/ObjectPrimitives.hpp"

#include "Routines/SystemPrimitives.hpp"



#include "PrimitiveDescription.hpp"
#include "PrimitiveTable.hpp"
#include "PrimitiveLoader.hpp"


Primitives::PrimitiveTable* Primitives::initializePrimitiveTable(unsigned short length) {
	Primitives::_table = new Primitives::PrimitiveTable(length);
	Primitives::loadPrimitives();
	return Primitives::_table;
}

void Primitives::loadPrimitive(const char* name, unsigned short parameterCount, Objects::SlotObject* (*routine)(Runtime::Metaverse*, Objects::SlotObject**)) {
	Primitives::_table->addPrimitive(Primitives::PrimitiveDescription(
		name,
		parameterCount,
		routine
	));
}

void Primitives::loadPrimitives() {
	// Array primitives
	loadPrimitive("byteAt",			2, Primitives::byteAt);
	loadPrimitive("byteAtPut",		3, Primitives::byteAtPut);
	loadPrimitive("objectAtPut",	2, Primitives::objectAt);
	loadPrimitive("objectAtPut",	3, Primitives::objectAtPut);
	loadPrimitive("getArrayLength", 1, Primitives::getArrayLength);
	loadPrimitive("resizeArray",	1, Primitives::resizeArray);
	
	//Integer primitives
	loadPrimitive("addSmi", 2, Primitives::addSmi);
	loadPrimitive("subSmi", 2, Primitives::subSmi);
	loadPrimitive("mulSmi", 2, Primitives::mulSmi);
	loadPrimitive("divSmi", 2, Primitives::divSmi);

	//Mirror primitives
	loadPrimitive("reflect",				1, Primitives::reflect);
	loadPrimitive("createNormalSlot",		3, Primitives::createNormalSlot);
	loadPrimitive("createParentSlot",		3, Primitives::createParentSlot);
	loadPrimitive("createNormalParameter",	3, Primitives::createNormalParameter);
	loadPrimitive("createParentParameter",	3, Primitives::createParentParameter);
	loadPrimitive("removeSlot",				2, Primitives::removeSlot);
	loadPrimitive("getSlotValue",			2, Primitives::getSlotValue);

	//SlotObject primitives
	loadPrimitive("clone",		1, Primitives::clone);
	loadPrimitive("identity",	2, Primitives::clone);

	//System primitives
	loadPrimitive("haltingError", 1, Primitives::haltingError);
	

}