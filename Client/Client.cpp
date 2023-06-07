#include "Client.h"
#include <fstream>
#include <iostream>

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
    const Client& driver = (const Client&)(user);
    file << "C" << " ";
    file << driver.firstName << " ";
    file << driver.lastName << " ";
    file << driver.username << " ";
    file << driver.password << " ";
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
            Client* client = new Client(firstName, lastName, username, password);
            registeredUsers.pushBack(client);
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

bool Client::login()
{
    const char* fileName = "clientUsers.txt";
    Vector<User*> registeredUsers = loadRegisteredUserFromFile(fileName);

    MyString username, password;
    std::cout << "Enter your username: ";
    std::cin >> username;
    std::cout << "Enter your password: ";
    std::cin >> password;

    for (int i = 0; i < registeredUsers.getSize(); i++)
    {
        if ((*registeredUsers[i]).getUsername() == username && (*registeredUsers[i]).getPassword() == password)
        {
            std::cout << "Welcome, " << (*registeredUsers[i]).getFirstName() << "!\n";
            return true;
        }
    }

    std::cout << "Invalid username or password!\n";
    return false;
}

User* Client::clone() const
{
    return new Client(*this);
}

void Client::placeOrder(const Address& address, const Address& destination, int numberOfPassengers, OrderManager& orders)
{
    Order newOrder(address, destination, numberOfPassengers);

    orders.addOrder(newOrder);

    std::cout << "Order placed successfully. Order ID: " << newOrder.getId() << std::endl;
}

Status Client::checkOrderStatus(OrderManager& orders, unsigned int id)
{
    Order* orderToBeFound = orders.findOrderById(id);
    return orderToBeFound->getStatus();
}

void Client::cancelOrder(OrderManager& orders, unsigned int orderId)
{
    orders.removeOrder(orderId);
}

void Client::payOrder(Order& order, double amount)
{
    order.setPaymentAmount(amount);
    order.setPaymentStatus(PaymentStatus::Paid);
}

void Client::addMoney(double amount)
{
    balance += amount;
}