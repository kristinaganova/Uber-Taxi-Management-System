#include "ClientMenuHandler.h"

ClientMenuHandler::ClientMenuHandler(UniquePointer<User> user, OrderManager& orderMgr)
    : loggedInUser(std::move(user)), orderManager(orderMgr) {}

void ClientMenuHandler::handleMenu()
{
    Client* client = static_cast<Client*>(loggedInUser.release());
    bool exitMenu = false;

    while (!exitMenu)
    {
        unsigned int clientChoice = displayMenu();

        switch (clientChoice)
        {
        case 1:
        {
            Address current;
            std::cout << "Enter your current address:" << std::endl;
            current.enterAddressDetails();

            std::cout << "Enter your destination address:" << std::endl;
            Address destination;
            destination.enterAddressDetails();

            std::cout << "Enter the number of passengers: ";
            int numberOfPassengers;
            std::cin >> numberOfPassengers;

            client->placeOrder(current, destination, numberOfPassengers);
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
        {
            client->checkMessages();
            break;
        }
        case 5:
        {
            MyString firstName;
            MyString lastName;

            int rating;
            std::cout << "Enter first name of the driver: " << std::endl;
            std::cin >> firstName;
            std::cout << "Enter last name of the driver: " << std::endl;
            std::cin >> lastName;
            std::cout << "Enter rating from 1 to 5: " << std::endl;
            std::cin >> rating;
            client->rateDriver(firstName, lastName, rating);
            std::cout << "Rating set successfully! " << std::endl;
            break;
        }
        case 6:
        {
            double amount;
            std::cout << "Enter amount of money to add: " << std::endl;
            std::cin >> amount;
            client->addMoney(amount);
            std::cout << "Money added successfully! " << std::endl;
            std::cout << "Your balance is " << client->getBalance() << std::endl;

            UserManager& users = UserManager::getInstance();
            users.clearAndSaveAllRegisteredClientsToFile("ClientUsers.txt");
            break;
        }
        case 7:
        {
            loggedInUser->logout();
            exitMenu = true;
            break;
        }
        default:
        {
            std::cout << "Invalid option. Please try again." << std::endl;
            break;
        }
        loggedInUser.release();
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
    std::cout << "4. Check messages" << std::endl;
    std::cout << "5. Rate Driver" << std::endl;
    std::cout << "6. Add money" << std::endl;
    std::cout << "7. Logout" << std::endl;
    std::cout << "Enter your choice: ";

    while (!(std::cin >> choice))
    {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Invalid input. Please try again: ";
    }

    return choice;
}
