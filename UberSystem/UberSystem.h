#pragma once
#include "OrderManager.h"
#include "MessageManager.h"
#include "UserManager.h"
#include "User.h"
#include "UniquePtr.hpp"
#include "MenuHandler.h"

class UberSystem
{
    UniquePointer<UserManager> users;
    UniquePointer<OrderManager> orderManager;
    UniquePointer<MessageManager> messageManager;
    UniquePointer<User> loggedInUser;

public:
    UberSystem();

    void run();
    int displayMainMenu();

    //for all
    void login();
    void registerUser();    
    void handleMenu(MenuHandler& menuHandler);
};       