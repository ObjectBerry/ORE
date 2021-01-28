#pragma once
namespace Runtime {
	class Metaverse; 
}
namespace Objects {
	class Object;
}

#define HeadRoutine(name) Objects::Object* name(Runtime::Metaverse* metaverse ,Objects::Object** parameters)
#define FullRoutine(name) Objects::Object* Primitives::name(Runtime::Metaverse* metaverse, Objects::Object** parameters) 

#define returnError(error) reinterpret_cast<Objects::Object*>(metaverse->getObjectUniverse()->createString(error))
