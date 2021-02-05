#pragma once
#include "PrimitiveUtil.hpp"

namespace Primitives {
	HeadRoutine(byteAt);
	HeadRoutine(byteAtPut);

	HeadRoutine(objectAt); 
	HeadRoutine(objectAtPut);

	HeadRoutine(getArrayLength);
	HeadRoutine(resizeArray);
}