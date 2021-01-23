#include <limits>

#include "../../Objects/SmallInt.hpp"
#include "../../Objects/ObjectFactory.hpp"
#include "../../Runtime/DependencyContainer.hpp"

#include "IntegerPrimitives.hpp"


#define testSmi not ((parameters[0]->getType() == Objects::ObjectType::SmallInt) && (parameters[1]->getType() == Objects::ObjectType::SmallInt))


#define castInt \
	long long first = static_cast<Objects::SmallInt*>(parameters[0])->getValue(); \
	long long second = static_cast<Objects::SmallInt*>(parameters[1])->getValue(); 

#define isOwerflow (result < INT_MIN || result > INT_MAX)

#define op(message) long long result = first message second

FullRoutine(addSmi) {
	if (testSmi) {
		return returnError("TypeError");
	}
	castInt;
	op(+);
	if (isOwerflow) {
		return returnError("OverflowError");
	}
	return dc->getObjectFactory()->createSmallInt(result);
}
FullRoutine(subSmi) {
	if (testSmi) {
		return returnError("TypeError");
	}
	castInt;
	op(-);
	if (isOwerflow) {
		return returnError("OverflowError");
	}
	return dc->getObjectFactory()->createSmallInt(result);
}
FullRoutine(mulSmi) {
	if (testSmi) {
		return returnError("TypeError");
	}
	castInt;
	op(*);
	if (isOwerflow) {
		return returnError("OverflowError");
	}
	return dc->getObjectFactory()->createSmallInt(result);
}
FullRoutine(divSmi) {
	if (testSmi) {
		return returnError("TypeError");
	}
	castInt;
	if (second == 0) {
		return returnError("DivisionByZeroError"); 
	}
	op(/);
	if (isOwerflow) {
		return returnError("OverflowError");
	}
	return dc->getObjectFactory()->createSmallInt(result);
}