#pragma once
namespace Objects {
	
	class ByteArray;
	class Object;
	class ObjectArray;
	class SmallInt;
	class Symbol;

	class ObjectFactory;
}
namespace Compiler {
	struct CodeDescription {
		Objects::ObjectArray*	_literals;
		Objects::ByteArray* _bytecodes;
	};

	class ByteTranslator {
		Objects::ObjectFactory* _objectFactory;
		char*					_bytes;
		unsigned short			_index;
		unsigned short			_lenght;
		
	public:
		
		Compiler::ByteTranslator(Objects::ObjectFactory* objectFactory, char* bytes, unsigned short length);

	private:
		bool isLimit(unsigned short requestedBytes);
		int translateNumber(unsigned char numberBytes);

	public:
		Objects::Object*	translateLiteral();
		Objects::SmallInt*	translateSmallInt();
		Objects::Symbol*	translateSymbol();
		CodeDescription     translateCode();
		Objects::Object*	translateObject();

	};
}