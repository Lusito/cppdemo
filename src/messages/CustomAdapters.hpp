#pragma once
#include "CustomMessages.hpp"

namespace eznet {
	void readMessage(BufferReader& reader, MyCustomStruct& message);
	void writeMessage(BufferWriter& writer, const MyCustomStruct& message);
	size_t getMessageSize(const MyCustomStruct& message);
	
	void readMessage(BufferReader& reader, nk_color& message);
	void writeMessage(BufferWriter& writer, const nk_color& message);
	size_t getMessageSize(const nk_color& message);
}
