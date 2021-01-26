#pragma once
namespace Objects {
	class Assignment;
	class ByteArray;
	class Object;
	class ObjectArray;
	class SmallInt;
	class String;
	class Symbol;
}
namespace Runtime {
	class ObjectUniverse;
}

namespace Compiler {
	struct CodeDescription {
		Objects::ObjectArray*	_literals;
		Objects::ByteArray* _bytecodes;
	};

	class ByteTranslator {
		Runtime::ObjectUniverse*	_objectUniverse;
		char*						_bytes;
		unsigned short				_index;
		unsigned short				_lenght;
		
	public:
		
		Compiler::ByteTranslator(Runtime::ObjectUniverse* objectUniverse, char* bytes, unsigned short length);

	private:
		void isLimit(unsigned short requestedBytes);
		int translateNumber(unsigned char numberBytes);

	public:
		Objects::Object*		translateLiteral();
		Objects::Assignment*	translateAssignment();
		Objects::SmallInt*		translateSmallInt();
		Objects::String*		translateString();
		Objects::Symbol*		translateSymbol();
		CodeDescription			translateCode();
		Objects::Object*		translateObject();
		Objects::Object*		translateMethod();

		CodeDescription			translateFile();
	};
}