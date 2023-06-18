#include "Client.h"
#include <fstream>
#include <iostream>
#include <memory>
#include "SharedPtr.hpp"
#include "Vector.hpp"
#include <sstream>

Client::Client(const MyString& firstName, const MyString& lastName, const MyString& username, const MyString& password)
    : User(UserType::CLIENT, firstName, lastName, username, password), balance(0) {}

Client::Client(const MyString& firstName, const MyString& lastName, const MyString& username, const MyString& password, double balance)
    : User(UserType::CLIENT, firstName, lastName, username, password) , balance(balance) {}

Client::Client() : balance(0) {}

void Client::setBalance(double balance)
{
    this->balance = balance;
}

double Client::getBalance() const
{
    return balance;
}

void Client::saveRegisteredUserToFile(const User& user, const char* fileName)
{
    std::ofstream file(fileName, std::ios::app);
    if (!file.is_open())
    {
        std::cout << "Error: Unable to open file " << fileName << " for writing." << std::endl;
        return;
    }
    const Client& driver = static_cast<const Client&>(user);
    file << "C" << " ";
    file << driver.firstName << " ";
    file << driver.lastName << " ";
    file << driver.username << " ";
    file << driver.password << " ";
    file << driver.balance << " ";
    file << std::endl;

    file.close();
}

Vector<User*> Client::loadRegisteredUserFromFile(const char* fileName)
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
     
        if (userTypeChar == 'C')
        {
            double balance;
            file >> balance;
            Client* client = new Client(firstName, lastName, username, password, balance);
            registeredUsers.pushBack(client);
        }
        else if(userTypeChar == 'D')
        {
            MyString carNumber;
            file >> carNumber;
            MyString phoneNumber;
            file >> phoneNumber;
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

void Client::registerUser()
{
    MyString firstName, lastName, username, password;

    std::cout << "Please enter your first name: ";
    std::cin >> firstName;

    std::cout << "Please enter your last name: ";
    std::cin >> lastName;

    std::cout << "Please enter a username (6-30 characters, alphanumeric only): ";
    std::cin >> username;

    std::cout << "Please enter a password (6-30 characters, alphanumeric only): ";
    std::cin >> password;

    Client newUser(firstName, lastName, username, password);
    saveRegisteredUserToFile(newUser, "ClientUsers.txt");

    std::cout << "Registration successful. Welcome, " << firstName << "!" << std::endl;
}

User* Client::clone() const
{
    return new Client(firstName, lastName, username, password, balance);
}

void Client::checkMessages()
{
    messages->printUnreadMessages();
}

void Client::placeOrder(const Address& address, const Address& destination, int numberOfPassengers)
{
    OrderManager& orders = *OrderManager::getInstance();
    Order newOrder(address, destination, numberOfPassengers , Status::Pending, PaymentStatus::NotPaid, 0.0, this, nullptr);
    //newOrder.setClient(this);
    orders.addOrder(newOrder);
    orders.notifyDriversInRange(newOrder);

    std::cout << "Order placed successfully. Order ID: " << newOrder.getId() << std::endl;
}

Status Client::checkOrderStatus(OrderManager& orders, unsigned int id)
{
    Order* orderToBeFound = orders.findOrderById(id);
    return orderToBeFound->getStatus();
}

void Client::cancelOrder(OrderManager& orders, unsigned int orderId)
{
    if(orders.findOrderById(orderId)->getStatus() == Status::Accepted)
    {
        SharedPtr<Driver> driver = orders.findOrderById(orderId)->getDriver();
        driver->getMessages()->addMessage(Message("Your order has been accepted" + driver->getFirstName(), driver->getMessages()->getNextId()));
    }
   
    orders.removeOrder(orderId);
}

void Client::rateDriver(const MyString& name,  int rating)
{
    UserManager& users = UserManager::getInstance();
    Driver* driver = static_cast<Driver*>(users.findUserByName(name));

    if (driver)
    {
        Rating r(rating, this);
        driver->addRating(r);
        std::cout << "Driver " << driver->getFirstName() << " rated successfully." << std::endl;
    }
    else
    {
        std::cout << "Driver not found. Unable to rate." << std::endl;
    }
}

void Client::payOrder(Order& order, double amount)
{
    order.setPaymentAmount(amount);
    order.setPaymentStatus(PaymentStatus::Paid);
    balance -= amount;
}

void Client::addMoney(double amount)
{
    balance += amount;
}