#pragma once
namespace Compiler {
	enum class LiteralType : unsigned char {
		Undefined		= 0x00,
		AssignmentLit	= 0x0A,

		SmallIntLit		= 0x10,
		FloatLit		= 0x11,

		StringLit		= 0xA0,
		SymbolLit		= 0xA1,

		ObjectLit		= 0xB0,
		MethodLit		= 0xBC,
		EvalLit			= 0xBF,

	};
}