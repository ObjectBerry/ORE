#pragma once

namespace Interpreter {
	/* Bytecodes is static class that is used to represent bytecode instructions
	// It also contain method to calculate lenght of every instruction in bytes
	*///
	class Bytecodes {
	public:
		enum class Instructions{
			ReturnTop,

			PushLiteral,
			PushSelf,
			Pop,

			Send,
			SendMyself,
			Resend,
		};

		static unsigned char instructionLength(Instructions instruction);
	};
}

