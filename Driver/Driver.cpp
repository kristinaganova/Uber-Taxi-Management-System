#include "Driver.h"
#include "Order.h"
#include "helpers.h"
#include <fstream>
#include "UniquePtr.hpp"

Driver::Driver(const MyString& firstName, const MyString& lastName, const MyString& username, 
               const MyString& password, const MyString& carNumber, const MyString& phoneNumber)
      :User(UserType::DRIVER , firstName, lastName, username, password), orders(*OrderManager::getInstance()), ratings()
{
    setCarNumber(carNumber);
    setPhoneNumber(phoneNumber);
}

Driver::Driver() :orders(*OrderManager::getInstance()) {}

const MyString& Driver::getCarNumber() const
{
    return carNumber;
}

const MyString& Driver::getPhoneNumber() const
{
    return phoneNumber;
}

const Address& Driver::getCurrentAddress() const
{
    return currentAddress;
}

void Driver::setCarNumber(const MyString& carNumber)
{
    if (carNumber.length() != 4)
    {
        throw std::invalid_argument("The number of car should be 4 digits");
    }

    for (size_t i = 0; i < 4; i++)
    {
        if (!isDigit(carNumber[i]))
        {
            throw std::invalid_argument("The car number only contains digits");
        }
    }
    this->carNumber = carNumber;
}

void Driver::setPhoneNumber(const MyString& phoneNumber)
{
    if (phoneNumber.length() != 10)
    {
        throw std::invalid_argument("The phone number should be 10 digits");
    }
    for (size_t i = 0; i < 10; i++)
    {
        if (!isDigit(phoneNumber[i]))
        {
            throw std::invalid_argument("The phone number only contains digits");
        }
    }

    this->phoneNumber = phoneNumber;
}

void Driver::registerUser()
{
    MyString firstName, lastName, username, password, carNumber, phoneNumber;

    std::cout << "Please enter your first name: ";
    std::cin >> firstName;

    std::cout << "Please enter your last name: ";
    std::cin >> lastName;

    std::cout << "Please enter a username (6-30 characters, alphanumeric only): ";
    std::cin >> username;

    std::cout << "Please enter a password (6-30 characters, alphanumeric only): ";
    std::cin >> password;

    std::cout << "Please enter a car number (4 characters, digits only): ";
    std::cin >> carNumber;

    std::cout << "Please enter a phone number (10 characters, digits only): ";
    std::cin >> phoneNumber;

    Driver newUser(firstName, lastName, username, password, carNumber, phoneNumber);
    saveRegisteredUserToFile(newUser, "driverUsers.txt");

    std::cout << "Registration successful. Welcome, " << firstName << "!" << std::endl;
}

User* Driver::clone() const
{
    return new Driver(firstName, lastName, username, password, carNumber, phoneNumber);
}

void Driver::saveRegisteredUserToFile(const User& user, const char* fileName) 
{
    std::ofstream file(fileName, std::ios::out | std::ios::app);
    if (!file)
    {
        std::cerr << "Error: Could not open file " << fileName << " for writing!" << std::endl;
        return;
    }

    const Driver& driver = (const Driver&)(user); 
    file << "D" << " ";
    file << driver.firstName << " ";
    file << driver.lastName << " ";
    file << driver.username << " ";
    file << driver.password << " ";
    file << driver.carNumber << " ";
    file << driver.phoneNumber << " ";
    file << std::endl;

    file.close();
}

Vector<User*> Driver::loadRegisteredUserFromFile(const char* fileName)
{
    std::ifstream file(fileName);
    if (!file.is_open())
    {
        std::cout << "Error: Unable to open file " << fileName << " for reading." << std::endl;
        static Vector<User*> emptyVector;
        return emptyVector;
    }

    Vector<User*> registeredUsers;

    char userTypeChar;
    while (file >> userTypeChar)
    {
        MyString firstName;
        file >> firstName;
        MyString lastName;
        file >> lastName;
        MyString username;
        file >> username;
        MyString password;
        file >> password;
        MyString carNumber;
        file >> carNumber;
        MyString phoneNumber;
        file >> phoneNumber;

        if (userTypeChar == 'D')
        {
            Driver* driver = new Driver(firstName, lastName, username, password, carNumber, phoneNumber);
            registeredUsers.pushBack(driver); 
        }
        else
        {
            std::cout << "Error: Invalid driver information found in file." << std::endl;
            continue;
        }
    }

    file.close();

    return registeredUsers;
}

void Driver::changeAddress(const Address& address)
{
    this->currentAddress = address;
    std::cout << "Address changed to: " << address.getName() << std::endl;
}

void Driver::checkMessages()
{   
     messages->printUnreadMessages();
}

void Driver::acceptOrder(unsigned int id)
{
    Order* foundOrder = orders.findOrderById(id);
    if (foundOrder)
    {
        SharedPtr<Client> client = foundOrder->getClient();
        if (client)
        {
            foundOrder->setStatus(Status::Accepted);
            foundOrder->setDriver(this);
            Message message("Your order has been accepted!", client->getMessages()->getNextId());
            client->getMessages()->addMessage(message);
            std::cout << "Order accepted successfully!" << std::endl;
        }
        else
        {
            std::cout << "Order was not accepted successfully!" << std::endl;
        }
    }
    else
    {
        std::cout << "No order with ID:" << id << "found!" << std::endl;
    }
}

void Driver::declineOrder(unsigned int id)
{
    Order* foundOrder = orders.findOrderById(id);
    if (foundOrder)
    {
        foundOrder->setStatus(Status::Canceled);
        std::cout << "Order declined successfully" << std::endl;
    }
}

void Driver::finishOrder(unsigned int id, double amountToBePaid)
{
    Order* foundOrder = orders.findOrderById(id);

    if (foundOrder)
    {
        SharedPtr<Client> client = foundOrder->getClient();
        if (client)
        {
            foundOrder->setStatus(Status::Completed);
            foundOrder->setPaymentAmount(amountToBePaid);
            client->payOrder(*foundOrder, amountToBePaid);
            Message message(("You paid " + MyString::valueOf(amountToBePaid)), client->getMessages()->getNextId());
            client->getMessages()->addMessage(message);
            foundOrder->setPaymentStatus(PaymentStatus::Paid);
            std::cout << "Order finished successfully!" << std::endl;
        }
        else
        {
            std::cout << "Order was not finished successfully!" << std::endl;
        }
    }
    else
    {
        std::cout << "The order was not found" << std::endl;
        return;
    }
}

void Driver::addRating(const Rating& rating)
{
    ratings.pushBack(rating);
}

void Driver::assignMessage(unsigned int messageID)
{
    Message* message = messages->getMessageById(messageID);

    if (message)
    {
        messages->addMessage(*message);
    }
}

double Driver::getAverageRating() const
{
    if (ratings.empty())
        return 0.0;

    int totalRating = 0;
    for (int i = 0; i< ratings.getSize(); i++)
    {
        totalRating += ratings[i].getRating();
    }

    return (double)((totalRating) / ratings.getSize());
}
