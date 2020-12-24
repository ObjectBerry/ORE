#include "SlotDescription.hpp"
#include "ObjectMap.hpp"

#include "SlotIterator.hpp"


Object_Layout::SlotIterator::SlotIterator(Object_Layout::ObjectMap* iteratedMap) {
	this->_activeDescription = iteratedMap->getSlotDescriptions();
	this->_lastDescription = this->_activeDescription + (iteratedMap->getSlotCount());
}

Object_Layout::SlotDescription* Object_Layout::SlotIterator::nextItem() {
	return this->_activeDescription++;
};
bool Object_Layout::SlotIterator::isEnd() {
	return this->_activeDescription == this->_lastDescription;
};