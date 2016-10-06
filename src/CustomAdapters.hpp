#pragma once
#include "CustomMessages.hpp"

namespace eznet {
	void readMessage(BufferReader& reader, MyCustomStruct& message);
	void writeMessage(BufferWriter& writer, const MyCustomStruct& message);
	size_t getMessageSize(const MyCustomStruct& message);
}
