#pragma once

namespace Objects {
	class Object;
	class Symbol;
}
namespace Sending {
	enum class LookupState;
	struct LookupResult;
	class ObjectQueue;
}

namespace Sending {
	class SendMachine {
		ObjectQueue* visitedQueue;
		ObjectQueue* lookupQueue;
		ObjectQueue* storageQueue;

		Sending::LookupResult lookupFor(Objects::Symbol* slotName);

	public:
		SendMachine(unsigned char parentQueueSize, unsigned char lookupQueueSize, unsigned char storageQueueSize);

		Sending::LookupResult sendMessage(Objects::Object* reciever, Objects::Symbol* selector, bool isResend);

	};
	
}