#pragma once

namespace Interpreter {
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

