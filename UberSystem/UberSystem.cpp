#include "UberSystem.h"
#include "Order.h"
#include "MenuHandler.h"
#include "ClientMenuHandler.h"
#include "DriverMenuHandler.h"

static void exitFunction() 
{
    OrderManager::getInstance()->saveAllUnfinishedOrdersInFile("unfinishedOrders.txt");
}

static void startFunction()
{
    OrderManager::getInstance()->loadAllUnfinishedOrdersFromFile("unfinishedOrders.txt");
}

UberSystem::UberSystem() : loggedInUser(nullptr), users(&UserManager::getInstance()), orderManager(OrderManager::getInstance()), messageManager(&MessageManager::getInstance()) {}

void UberSystem::run()
{
    startFunction();
    bool loggedIn = false;

    while (true)
    {
        if (!loggedIn)
        {
            int choice = displayMainMenu();

            switch (choice)
            {
            case 1:
                login();
                loggedIn = true;
                break;
            case 2:
                registerUser();
                break;
            case 3:
                std::cout << "Exiting the Uber System..." << std::endl;
                return;
            default:
                std::cout << "Invalid option. Please try again." << std::endl;
                break;
            }
        }
        else
        {
            if (loggedInUser)
            {
                std::cout << "Welcome, " << loggedInUser->getUsername() << "!" << std::endl;

                if (loggedInUser->getUserType() == UserType::CLIENT)
                {
                    ClientMenuHandler clientMenuHandler(std::move(loggedInUser), *orderManager);
                    handleMenu(clientMenuHandler);
                }
                else if (loggedInUser->getUserType() == UserType::DRIVER)
                {
                    DriverMenuHandler driverMenuHandler(std::move(loggedInUser), *messageManager);
                    handleMenu(driverMenuHandler);
                }
                else
                {
                    std::cout << "Invalid user type. Please try again." << std::endl;
                }
            }
            else
            {
                std::cout << "Error: No logged-in user found." << std::endl;
                loggedIn = false;
            }
        }
    }
    exitFunction();
}

int UberSystem::displayMainMenu()
{
    int choice;
    std::cout << "Main Menu:" << std::endl;
    std::cout << "1. Login" << std::endl;
    std::cout << "2. Register" << std::endl;
    std::cout << "3. Exit" << std::endl;
    std::cout << "Enter your choice: ";
    std::cin >> choice;
    return choice;
}

void UberSystem::login()
{
    users->loadAllUsersFromFile();

    if (!loggedInUser)
    {
        MyString username, password;
        std::cout << "Enter your username: ";
        std::cin >> username;
        std::cout << "Enter your password: ";
        std::cin >> password;

        UniquePointer<User> user = users->findUserByUserName(username);

        if (user->login(username, password))
        {
            loggedInUser = std::move(user);
            std::cout << "Login successful!" << std::endl;
            return;
        }
        else
        {
            std::cout << "Login failed!" << std::endl;
            loggedInUser = nullptr;
        }
    }
}

void UberSystem::registerUser()
{
    int userTypeChoice;
    std::cout << "Select user type: " << std::endl;
    std::cout << "1. Client" << std::endl;
    std::cout << "2. Driver" << std::endl;
    std::cout << "Enter your choice: " << std::endl;
    std::cin >> userTypeChoice;

    User* newUser = nullptr;

    switch (userTypeChoice)
    {
    case 1:
    {
        newUser = new Client();
        break;
    }
    case 2:
    {
        newUser = new Driver();
        break;
    }
    default:
    {
        std::cout << "Invalid user type choice!" << std::endl;
        return;
    }
    }

    if (newUser)
    {
        newUser->registerUser();
        users->addUser(newUser);
        std::cout << "Registration successful!" << std::endl;
    }
}

void UberSystem::handleMenu(MenuHandler& menuHandler)
{
    menuHandler.handleMenu();
}