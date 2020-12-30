#include "Bytecodes.hpp"

unsigned char Interpreter::Bytecodes::instructionLength(Instructions instruction) {
	switch (instruction) {
	case Instructions::Pop:
	case Instructions::PushSelf:
	case Instructions::SendMyself:
	case Instructions::Resend:
	case Instructions::ReturnTop:
		return 1;

	case Instructions::PushLiteral:
		return 2;
	};
}
