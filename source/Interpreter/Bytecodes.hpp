#pragma once

namespace Interpreter {
	/* Bytecodes is static class that is used to represent bytecode instructions
	// It also contain method to calculate lenght of every instruction in bytes
	*///
	class Bytecodes {
	public:
		enum class Instructions : unsigned char{
			ReturnTop		= 0x01,

			PushLiteral		= 0x10,
			PushSelf		= 0x11,
			Pop				= 0x1A,

			Send			= 0x20,
			VMSend			= 0x21 ,
			SendMyself      = 0x22,
			Resend          = 0x2A,
		};

		static unsigned char instructionLength(Instructions instruction);
	};
}

