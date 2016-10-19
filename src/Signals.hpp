#pragma once
#include <signal11/Signal.hpp>
#include <string>

enum class DisconnectReason : uint8_t;
struct NetPlayerInfo;

struct Signals {
	static Signals *getInstance() {
		static Signals instance;
		return &instance;
	}

	Signal<void (const std::string &message)> error;
	Signal<void ()> serverConnected; // emitted on client
	Signal<void (DisconnectReason reason)> serverDisconnected; // emitted on client
	Signal<void (NetPlayerInfo *info)> clientConnected;// emitted on server
	Signal<void (NetPlayerInfo *info)> clientDisconnected;// emitted on server
};
