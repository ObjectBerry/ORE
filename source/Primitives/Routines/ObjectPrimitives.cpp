#include "../../Runtime/ObjectUniverse.hpp"
#include "../../Runtime/Metaverse.hpp"
#include "../../Objects/Object.hpp"

#include "ObjectPrimitives.hpp"

FullRoutine(clone) {
	return parameters[0]->clone(metaverse->getBasicAllocator());
}
FullRoutine(identity) {
	bool result = parameters[0]->identical(parameters[1]);
	return result ?
		metaverse->getObjectUniverse()->getTrueObject() :
		metaverse->getObjectUniverse()->getFalseObject();
}
