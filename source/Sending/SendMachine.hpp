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
		ObjectQueue* _visitedQueue;
		ObjectQueue* _lookupQueue;
		ObjectQueue* _parentQueue;

		Sending::LookupResult lookupFor(Objects::Symbol* slotName);
		void addParentsFrom(Objects::Object* lookupedObject);

	public:
		SendMachine(unsigned char parentQueueSize, unsigned char lookupQueueSize, unsigned char visitedQueueSize);
		~SendMachine();

		Sending::LookupResult sendMessage(Objects::Object* reciever, Objects::Symbol* selector, bool isResend);

	};
	
}