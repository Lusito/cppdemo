#include "../../generated/MessageAdapters.hpp"

namespace eznet {
	void readMessage(BufferReader& reader, MyCustomStruct& message) {
		readMessage(reader, message.value1);
		readMessage(reader, message.value2);
	}
	void writeMessage(BufferWriter& writer, const MyCustomStruct& message) {
		writeMessage(writer, message.value1);
		writeMessage(writer, message.value2);
	}
	size_t getMessageSize(const MyCustomStruct& message){
		return getMessageSize(message.value1)+getMessageSize(message.value2);
	}
}
