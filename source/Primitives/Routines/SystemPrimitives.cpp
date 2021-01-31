#include "../../Interpreter/ExecutionEngine.hpp"
#include "../../Runtime/Metaverse.hpp"

#include "SystemPrimitives.hpp"

FullRoutine(haltingError) {
	metaverse->getExecutionEngine()->haltingError(parameters[0]);
}