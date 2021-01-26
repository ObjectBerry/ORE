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

	/* SendMachine is important part of ORE - it is giving support for message sending
	// It have only one public method - sendMessage - that is used to lookup for correct slot in object and object's parents
	*///
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