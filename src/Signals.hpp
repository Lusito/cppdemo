#pragma once
#include <signal11/Signal.hpp>

enum class DisconnectReason : uint8_t;
class NetPlayerInfo;

struct Signals {
	static Signals *getInstance() {
		static Signals instance;
		return &instance;
	}

	Signal<void ()> serverConnected; // emitted on client
	Signal<void (DisconnectReason reason)> serverDisconnected; // emitted on client
	Signal<void (NetPlayerInfo *info)> clientConnected;// emitted on server
	Signal<void (NetPlayerInfo *info)> clientDisconnected;// emitted on server
};
