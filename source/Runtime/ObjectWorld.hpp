#pragma once


namespace Objects {
	class Object;
	class ObjectFactory;
}

namespace Runtime {
	class ObjectWorld {
		Objects::ObjectFactory* _objectFactory;

		// important objects used by primitives
		Objects::Object* _trueObject;
		Objects::Object* _falseObject;
		Objects::Object* _undefinedObject;

		// object world basic structure
		Objects::Object* _lobbyObject;
		Objects::Object* _globalsObject;
		Objects::Object* _traitsObject;

	public:
		ObjectWorld(Objects::ObjectFactory* objectFactory);
	
	private:
		void setSlotNames(Object_Layout::ObjectMap* map, unsigned short nameCount, const char* names[]);
		void createFullPrototype(const char* name, Objects::Object* prototype);
		

	public:
		inline Objects::Object* getTrueObject()		{ return this->_trueObject; }
		inline Objects::Object* getFalseObject()	{ return this->_falseObject; }
		inline Objects::Object* getUndefined()		{ return this->_undefinedObject; }

		inline Objects::Object* getLobbyObject()	{ return this->_lobbyObject; }
		inline Objects::Object* getGlobalsObject()	{ return this->_globalsObject; }
		inline Objects::Object* getTraitsObject()	{ return this->_traitsObject; }
	};
}