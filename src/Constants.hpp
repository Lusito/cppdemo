#pragma once
#include <string>
#include <stdint.h>

enum class NetChannel : uint8_t {
	CHAT,
	WORLD_RELIABLE,
	WORLD_UNRELIABLE,
	INPUT_RELIABLE,
	INPUT_UNRELIABLE,

	COUNT
};

enum class ServerStatus : uint8_t {
	INIT,
	INGAME,
	SHUTDOWN
};

enum class DisconnectReason : uint8_t {
	DISCONNECT,
	CONNECT_FAILED
};

namespace Constants {
	const std::string GAME_NAME = "Cpp Demo";
	const uint16_t DISCOVERY_PORT = 1337;
	const uint16_t DEFAULT_PORT = 1234;
	const uint8_t MAX_SLOTS = 4;
	const uint16_t MAX_MESSAGE_SIZE = 1024;
}