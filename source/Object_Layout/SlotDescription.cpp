#include "../Memory/MemoryFacade.hpp"
#include "../Objects/Object.hpp"

#include "SlotDescription.hpp"

void* Object_Layout::SlotDescription::operator new[](size_t size, Memory::MemoryFacade* memoryFacade) {
	return memoryFacade->allocate(size);
}
Object_Layout::SlotDescription::SlotDescription() {
	this->slotData = nullptr;
}
