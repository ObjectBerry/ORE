#pragma once

namespace Objects {
	// Enum used for quessing entity type
	enum class ObjectType {
		SlotObject,


		MappedObject,
		ByteArray,
		Symbol, 
		ObjectArray,
		SmallInt,
		Code,
		Context,
		Process,
		Assignment,
		String,
		Mirror,
	};
}