#include "DriverMenuHandler.h"
#include "Driver.h"

void DriverMenuHandler::handleMenu()
{
    Driver* driver = static_cast<Driver*>(loggedInUser.get());
    bool exitMenu = false;

    while (!exitMenu)
    {
        unsigned int driverChoice = displayMenu();

        switch (driverChoice)
        {
        case 1:
        {
            std::cout << "Enter address: " << std::endl;
            Address address;
            std::cin >> address;
            driver->changeAddress(address);
            break;
        }
        case 2:
            driver->checkMessages();
            break;
        case 3:
        {
            std::cout << "Enter order id to accept: " << std::endl;
            unsigned int orderId;
            std::cin >> orderId;
            driver->acceptOrder(orderId);
            break;
        }
        case 4:
        {
            std::cout << "Enter order id to decline: " << std::endl;
            unsigned int orderId;
            std::cin >> orderId;
            driver->declineOrder(orderId);
            break;
        }
        case 5:
        {
            std::cout << "Enter order id you finished: " << std::endl;
            unsigned int orderId;
            std::cin >> orderId;
            driver->finishOrder(orderId);
            break;
        }
        case 6:
            loggedInUser->logout();
            loggedInUser.release();

            exitMenu = true;
            break;
        default:
            std::cout << "Invalid option. Please try again." << std::endl;
            break;
        }
    }
}

int DriverMenuHandler::displayMenu() const
{
    int choice;
    std::cout << "Driver Menu:" << std::endl;
    std::cout << "1. Change Address" << std::endl;
    std::cout << "2. Check Messages" << std::endl;
    std::cout << "3. Accept Order" << std::endl;
    std::cout << "4. Decline Order" << std::endl;
    std::cout << "5. Finish Order" << std::endl;
    std::cout << "6. Logout" << std::endl;
    std::cout << "Enter your choice: ";
    std::cin >> choice;
    return choice;
}
