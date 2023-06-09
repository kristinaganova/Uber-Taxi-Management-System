#include "ClientMenuHandler.h"

void ClientMenuHandler::handleMenu()
{
    Client* client = static_cast<Client*>(loggedInUser.get());
    bool exitMenu = false;

    while (!exitMenu)
    {
        unsigned int clientChoice = displayMenu();

        switch (clientChoice)
        {
        case 1:
        {
            Address current;
            std::cout << "Enter your current address: ";
            std::cin >> current;
            std::cout << "Enter your destination address: ";
            Address destination;
            std::cin >> destination;
            std::cout << "Enter passengers count: ";
            int numberOfPassengers;
            std::cin >> numberOfPassengers;

            client->placeOrder(current, destination, numberOfPassengers, *OrderManager::getInstance());
            break;
        }
        case 2:
        {
            std::cout << "Enter order id: " << std::endl;
            unsigned int id;
            std::cin >> id;
            Status result = client->checkOrderStatus(*OrderManager::getInstance(), id);
            std::cout << toStringStatus(result) << std::endl;
            break;
        }
        case 3:
        {
            unsigned int orderId;
            std::cout << "Enter the Order ID to cancel: ";
            std::cin >> orderId;
            client->cancelOrder(*OrderManager::getInstance(), orderId);
            break;
        }
        case 4:
            // handle rateDriver()
            break;
        case 5:
            loggedInUser->logout();
            loggedInUser.release();
            exitMenu = true; // Set the flag to exit the loop
            break;
        default:
            std::cout << "Invalid option. Please try again." << std::endl;
            break;
        }
    }
}

int ClientMenuHandler::displayMenu() const
{
    int choice;
    std::cout << "Client Menu:" << std::endl;
    std::cout << "1. Place Order" << std::endl;
    std::cout << "2. Check Order" << std::endl;
    std::cout << "3. Cancel Order" << std::endl;
    std::cout << "4. Rate Driver" << std::endl;
    std::cout << "5. Logout" << std::endl;
    std::cout << "Enter your choice: ";
    std::cin >> choice;
    return choice;
}
