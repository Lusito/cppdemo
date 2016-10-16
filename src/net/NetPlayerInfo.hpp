#pragma once
#include <string>
#include <ecstasy/core/Entity.hpp>
#include "../Constants.hpp"

enum class NetPlayerStatus {
	DISCONNECTED,
	CONNECTING,
	CONNECTED
};

struct _ENetPeer;
typedef _ENetPeer ENetPeer;

struct NetPlayerInfo {
	std::string name = "Connecting...";
	NetPlayerStatus status = NetPlayerStatus::DISCONNECTED;
	uint64_t entityId;
	uint8_t playerIndex;
	ENetPeer *peer = nullptr;

	void init(ENetPeer *_peer) {
		peer = _peer;
		name = "Connecting...";
		status = NetPlayerStatus::CONNECTING;
		entityId = 0;
	}

	void invalidate() {
		peer = nullptr;
		name = "?";
		status = NetPlayerStatus::DISCONNECTED;
		entityId = 0;
	}
};

struct NetPlayerInfos {
	NetPlayerInfo slots[Constants::MAX_SLOTS];
	
	NetPlayerInfos(const std::string &username) {
		for(uint8_t i = 0; i < Constants::MAX_SLOTS; i++) {
			slots[i].invalidate();
			slots[i].playerIndex = i;
			slots[i].name = "Player " + std::to_string(i);
		}
		slots[0].status = NetPlayerStatus::CONNECTED;
		slots[0].name = username;
	}

	void makeUniqueName(NetPlayerInfo* info) {
		bool changed;
		do {
			changed = false;
			for(int i = 0; i < Constants::MAX_SLOTS; i++) {
				if(info != &slots[i] && info->name == slots[i].name) {
					info->name += '#';
					changed = true;
				}
			}
		} while(changed);
	}
};