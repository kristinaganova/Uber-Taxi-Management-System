#pragma once
#include "MenuHandler.h"
#include "MessageManager.h"
#include "UniquePtr.hpp"
#include "User.h"

class DriverMenuHandler : public MenuHandler
{
private:
    UniquePointer<User> loggedInUser;
    MessageManager& messageManager;

public:
    DriverMenuHandler(UniquePointer<User> user, MessageManager& messageMgr)
        : loggedInUser(std::move(user)), messageManager(messageMgr) {}

    void handleMenu() override;
    int displayMenu() const override;
};