#pragma once


namespace Objects {
	class Object;
	class ObjectFactory;
}

namespace Runtime {
	class ObjectWorld {
		// important objects used by primitives
		Objects::Object* trueObject;
		Objects::Object* falseObject;
		Objects::Object* undefinedObject;

		// object world basic structure
		Objects::Object* lobbyObject;
		Objects::Object* globalsObject;
		Objects::Object* traitsObject;

	public:
		ObjectWorld(Objects::ObjectFactory* objectFactory);
	
	private:
		

	public:
		inline Objects::Object* getTrueObject()		{ return this->trueObject; }
		inline Objects::Object* getFalseObject()	{ return this->falseObject; }
		inline Objects::Object* getUndefined()		{ return this->undefinedObject; }

		inline Objects::Object* getLobbyObject()	{ return this->lobbyObject; }
		inline Objects::Object* getGlobalsObject()	{ return this->globalsObject; }
		inline Objects::Object* getTraitsObject()	{ return this->traitsObject; }
	};
}