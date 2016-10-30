#pragma once
#include "MenuPage.hpp"
#include <signal11/Signal.hpp>

class MenuPageCreateServer;
class MenuPageFindServers;
class MenuPageJoinServer;
class MenuPageError;
enum class DisconnectReason : uint8_t;
class MenuPageMain : public MenuPage {
private:
	std::shared_ptr<MenuPageCreateServer> createServerMenu;
	std::shared_ptr<MenuPageFindServers> findServersMenu;
	std::shared_ptr<MenuPageJoinServer> joinServerMenu;
	std::shared_ptr<MenuPageError> errorMenu;
	ConnectionScope connectionScope;

public:
	MenuPageMain(StateManager& manager, nk_context* nk);
	MenuPageMain(const MenuPageMain& orig) = delete;
	virtual ~MenuPageMain();

	virtual void updateContent();

private:
	void onError(const std::string &message);
	void onServerDisconnected(DisconnectReason reason);
};
