#pragma once
namespace Runtime {
	class DependencyContainer;
}
namespace Objects {
	class Object;
}

#define HeadRoutine(name) Objects::Object* name(Runtime::DependencyContainer* dc ,Objects::Object** parameters)
#define FullRoutine(name) Objects::Object* Primitives::name(Runtime::DependencyContainer* dc, Objects::Object** parameters)