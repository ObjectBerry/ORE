#pragma once
namespace Runtime {
	class Metaverse; 
}
namespace Objects {
	class SlotObject;
}

#define HeadRoutine(name) Objects::SlotObject* name(Runtime::Metaverse* metaverse ,Objects::SlotObject** parameters)
#define FullRoutine(name) Objects::SlotObject* Primitives::name(Runtime::Metaverse* metaverse, Objects::SlotObject** parameters) 

#define returnError(error) reinterpret_cast<Objects::SlotObject*>(metaverse->getObjectUniverse()->createString(error))
