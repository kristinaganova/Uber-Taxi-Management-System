#pragma once
#include "OrderManager.h"
#include "MessageManager.h"
#include "UserManager.h"
#include "User.h"
#include "UniquePtr.hpp"

class UberSystem
{
    OrderManager orderManager;
    MessageManager messageManager;
    UserManager users;
    UniquePointer<User> loggedInUser;

public:
    UberSystem();

    void run();
    int displayMainMenu();
    int displayClientMenu();
    int displayDriverMenu();

    void handleDriverMenu();
    void handleClientMenu();

    //for all
    void login();
    void registerUser();    
};       