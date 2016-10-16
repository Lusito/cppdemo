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
	
	void readMessage(BufferReader& reader, nk_color& message) {
		readMessage(reader, message.r);
		readMessage(reader, message.g);
		readMessage(reader, message.b);
		readMessage(reader, message.a);
	}
	void writeMessage(BufferWriter& writer, const nk_color& message) {
		writeMessage(writer, message.r);
		writeMessage(writer, message.g);
		writeMessage(writer, message.b);
		writeMessage(writer, message.a);
	}
	size_t getMessageSize(const nk_color& message){
		return getMessageSize(message.r)+getMessageSize(message.g)+getMessageSize(message.b)+getMessageSize(message.a);
	}
}
