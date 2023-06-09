#include "UberSystem.h"
#include "Order.h"

UberSystem::UberSystem() : loggedInUser(UniquePointer<User>(nullptr)), orderManager(), messageManager(), users() {}

void UberSystem::run()
{
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
                    handleClientMenu();
                }
                else if (loggedInUser->getUserType() == UserType::DRIVER)
                {
                    handleDriverMenu();
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
}

void UberSystem::handleClientMenu()
{
    Client* client = static_cast<Client*>(loggedInUser.get());

    while (true)
    {    
        unsigned int clientChoice = displayClientMenu();

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

            client->placeOrder(current, destination, numberOfPassengers, orderManager);
            break;
        }
        case 2:
        {
            std::cout << "Enter order id: " << std::endl;
            unsigned int id;
            std::cin >> id;
            Status result = client->checkOrderStatus(orderManager, id);
            std::cout << toStringStatus(result) << std::endl;
            break;
        }
        case 3:
        {
            unsigned int orderId;
            std::cout << "Enter the Order ID to cancel: ";
            std::cin >> orderId;
            client->cancelOrder(orderManager, orderId);
            break;
        }
        case 4:
            // handle rateDriver()
            break;
        case 5:
            loggedInUser->logout();
            loggedInUser = nullptr;
            return;
        default:
            std::cout << "Invalid option. Please try again." << std::endl;
            break;
        }
    }
}

void UberSystem::handleDriverMenu()
{
    Driver* driver = (Driver*)(loggedInUser.get());

    while (true)
    {
        unsigned int driverChoice = displayDriverMenu();
   
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
            loggedInUser = nullptr;
            return;
        default:
            std::cout << "Invalid option. Please try again." << std::endl;
            break;
        }
    }
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

int UberSystem::displayClientMenu()
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

int UberSystem::displayDriverMenu()
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

void UberSystem::login()
{
    users.loadAllUsersFromFile();

    if (!loggedInUser)
    {
        MyString username, password;
        std::cout << "Enter your username: ";
        std::cin >> username;
        std::cout << "Enter your password: ";
        std::cin >> password;

        UniquePointer<User> user = users.findUserByUserName(username);
        if (user)
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
    std::cout << "Select user type:\n";
    std::cout << "1. Client\n";
    std::cout << "2. Driver\n";
    std::cout << "Enter your choice: ";
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
        users.addUser(newUser);
        std::cout << "Registration successful!" << std::endl;
    }
}
