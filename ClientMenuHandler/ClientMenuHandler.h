#pragma once
#include "OrderManager.h"
#include "UniquePtr.hpp"
#include "MenuHandler.h"

class ClientMenuHandler : public MenuHandler
{
private:
    UniquePointer<User> loggedInUser;
    OrderManager& orderManager;

public:
    ClientMenuHandler(UniquePointer<User> user, OrderManager& orderMgr)
        : loggedInUser(std::move(user)), orderManager(orderMgr) {}

    void handleMenu() override;
    int displayMenu() const override;
};