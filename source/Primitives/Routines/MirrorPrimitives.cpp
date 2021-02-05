#include "../../Runtime/Metaverse.hpp"
#include "../../Object_Layout/SlotDescription.hpp"
#include "../../Object_Layout/SlotType.hpp"
#include "../../Object_Layout/ObjectMap.hpp"

#include "../../Runtime/ObjectUniverse.hpp"
#include "../../Objects/SmallInt.hpp"
#include "../../Objects/Symbol.hpp"

#include "../../Objects/Mirror.hpp"



#include "MirrorPrimitives.hpp"

#define TYPE_CHECK													\
	if (parameters[0]->getType() != Objects::ObjectType::Mirror) {	\
		return returnError("TypeError");							\
	}																\
	if (parameters[1]->getType() != Objects::ObjectType::Symbol) {	\
		return returnError("TypeError");							\
	}

#define CASTED_VARS \
  Objects::Object* mirroredObject = reinterpret_cast<Objects::Mirror*>(parameters[0])->getReflectee(); \
  Objects::Symbol* slotName = reinterpret_cast<Objects::Symbol*>(parameters[1]);


FullRoutine(reflect) {
	return metaverse->getObjectUniverse()->createMirror(parameters[0]);
}

FullRoutine(createNormalSlot) {
	TYPE_CHECK;
	CASTED_VARS;
	bool succesful = mirroredObject->createSlot(
		Object_Layout::SlotDescription(
			slotName,
			Object_Layout::SlotType::ParentSlot
		),
		parameters[3]
	);

	if (not succesful) {
		return returnError("SlotAlredyExistsError"); 
	}
	return metaverse->getObjectUniverse()->getUndefinedObject();
}

FullRoutine(createParentSlot) {
	TYPE_CHECK;
	CASTED_VARS;
	bool succesful = mirroredObject->createSlot(
		Object_Layout::SlotDescription(
			slotName,
			Object_Layout::SlotType::NormalParameter
		),
		parameters[3]
	);

	if (not succesful) {
		return returnError("SlotAlredyExistsError");
	}
	return metaverse->getObjectUniverse()->getUndefinedObject();
}

FullRoutine(createNormalParameter) {
	TYPE_CHECK;
	CASTED_VARS;
	if (not mirroredObject->hasCode()) {
		return returnError("ParameterInNormalObjectError");
	}
	
	bool succesful = mirroredObject->createSlot(
		Object_Layout::SlotDescription(
			slotName,
			Object_Layout::SlotType::ParentParameter
		),
		parameters[3]
	);
	
	if (not succesful) {
		return returnError("SlotAlredyExistsError");
	}
	return metaverse->getObjectUniverse()->getUndefinedObject();
}

FullRoutine(createParentParameter) {
	TYPE_CHECK;
	CASTED_VARS;
	if (not mirroredObject->hasCode()) {
		return returnError("ParameterInNormalObjectError");
	}
	
	bool succesful = mirroredObject->createSlot(
		Object_Layout::SlotDescription(
			slotName,
			Object_Layout::SlotType::NormalSlot
		),
		parameters[3]
	);

	if (not succesful) {
		return returnError("SlotAlredyExistsError");
	}
	return metaverse->getObjectUniverse()->getUndefinedObject();
}

FullRoutine(removeSlot) {
	TYPE_CHECK;

	CASTED_VARS;
	bool succesful = mirroredObject->removeSlot(slotName);

	if (not succesful) {
		return returnError("SlotDoesntExist");
	}

	return metaverse->getObjectUniverse()->getUndefinedObject();
}


FullRoutine(getSlotValue) {
	TYPE_CHECK;
	CASTED_VARS;

	Objects::Object* succesful = mirroredObject->getSlot(slotName);
	if (succesful == nullptr) {
		return returnError("SlotDoesntExist");
	}
	return succesful;
}