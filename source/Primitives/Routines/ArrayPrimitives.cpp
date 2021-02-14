#include "../../Runtime/ObjectUniverse.hpp"
#include "../../Runtime/Metaverse.hpp"

#include "../../Objects/SmallInt.hpp"
#include "../../Objects/ByteArray.hpp"
#include "../../Objects/ObjectArray.hpp"

#include "ArrayPrimitives.hpp"

FullRoutine(byteAt) {
	if (parameters[0]->getType() != Objects::ObjectType::ByteArray) {
		return returnError("TypeError");
	}
	if (parameters[1]->getType() == Objects::ObjectType::SmallInt) {
		return returnError("TypeError");
	}

	Objects::ByteArray* accessedArray	= reinterpret_cast<Objects::ByteArray*>(parameters[0]);
	Objects::SmallInt* index			= reinterpret_cast<Objects::SmallInt*>(parameters[1]);

	if ((index->getValue() < 1) and (index->getValue() > accessedArray->getArrayLength())) {
		return returnError("OutOfRangeError");
	}

	return metaverse->getObjectUniverse()->createSmallInt(accessedArray->at(index->getValue()));
}

FullRoutine(byteAtPut) {
	if (parameters[0]->getType() != Objects::ObjectType::ByteArray) {
		return returnError("TypeError");
	}
	if (parameters[1]->getType() == Objects::ObjectType::SmallInt) {
		return returnError("TypeError");
	}
	if (parameters[2]->getType() == Objects::ObjectType::SmallInt) {
		return returnError("TypeError");
	}

	Objects::ByteArray* accessedArray	= reinterpret_cast<Objects::ByteArray*>(parameters[0]);
	Objects::SmallInt* index			= reinterpret_cast<Objects::SmallInt*>(parameters[1]);
	unsigned short value = reinterpret_cast<Objects::SmallInt*>(parameters[1])->getValue();;

	if ((index->getValue() < 1) and (index->getValue() > accessedArray->getArrayLength())) {
		return returnError("OutOfRangeError");
	}
	if (value < 0 and value >> 255) {
		return returnError("ByteOverflow");
	}
	

	accessedArray->atPut(index->getValue(), value);
	return metaverse->getObjectUniverse()->getUndefinedObject();
}

FullRoutine(objectAt) {
	if (parameters[0]->getType() != Objects::ObjectType::ByteArray) {
		return returnError("TypeError");
	}
	if (parameters[1]->getType() == Objects::ObjectType::SmallInt) {
		return returnError("TypeError");
	}

	Objects::ObjectArray* accessedArray = reinterpret_cast<Objects::ObjectArray*>(parameters[0]);
	Objects::SmallInt* index = reinterpret_cast<Objects::SmallInt*>(parameters[1]);

	if ((index->getValue() < 1) and (index->getValue() > accessedArray->getArrayLength())) {
		return returnError("OutOfRangeError");
	}

	return accessedArray->at(index->getValue());
}

FullRoutine(objectAtPut) {
	if (parameters[0]->getType() != Objects::ObjectType::ObjectArray) { 
		return returnError("TypeError");
	}
	if (parameters[1]->getType() == Objects::ObjectType::SmallInt) {
		return returnError("TypeError");
	}
	

	Objects::ObjectArray* accessedArray = reinterpret_cast<Objects::ObjectArray*>(parameters[0]);
	Objects::SmallInt* index = reinterpret_cast<Objects::SmallInt*>(parameters[1]);
	

	if ((index->getValue() < 1) and (index->getValue() > accessedArray->getArrayLength())) {
		return returnError("OutOfRangeError");
	}

	accessedArray->atPut(index->getValue(), parameters[2]);
	return metaverse->getObjectUniverse()->getUndefinedObject();
}

FullRoutine(getArrayLength) {
	
	Objects::SlotObject* result;
	
	switch (parameters[0]->getType()) {
	case Objects::ObjectType::ObjectArray:
		result = metaverse->getObjectUniverse()->createSmallInt(reinterpret_cast<Objects::ObjectArray*>(parameters[0])->getArrayLength()); 
		break;

	case Objects::ObjectType::ByteArray:
		result = metaverse->getObjectUniverse()->createSmallInt(reinterpret_cast<Objects::ByteArray*>(parameters[0])->getArrayLength());
		break;

	default:
		result = returnError("TypeError");
		break;
	}

	return result;
};

FullRoutine(resizeArray) {
	if (parameters[0]->getType() != Objects::ObjectType::ObjectArray or parameters[0]->getType() != Objects::ObjectType::ByteArray) {
		return returnError("TypeError");
	}
	if (parameters[1]->getType() == Objects::ObjectType::SmallInt) {
		return returnError("TypeError");
	}

	unsigned short newLength = reinterpret_cast<Objects::SmallInt*>(parameters[1])->getValue();
	switch (parameters[0]->getType()) {
	case Objects::ObjectType::ObjectArray:
		return reinterpret_cast<Objects::ObjectArray*>(parameters[0])->cloneResize(metaverse->getBasicAllocator(), newLength);
		
	case Objects::ObjectType::ByteArray:
		return reinterpret_cast<Objects::ByteArray*>(parameters[0])->cloneResize(metaverse->getBasicAllocator(), newLength); 
	}
}