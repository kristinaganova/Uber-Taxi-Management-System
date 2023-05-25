#include "Driver.h"
#include "Order.h"
#include "helpers.h"
#include <fstream>

Driver::Driver(const MyString& firstName, const MyString& lastName, const MyString& username, 
               const MyString& password, const MyString& carNumber, const MyString& phoneNumber)
       :User(UserType::DRIVER , firstName, lastName, username, password)
{
    setCarNumber(carNumber);
    setPhoneNumber(phoneNumber);
}

Driver::Driver() = default;

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

bool Driver::login()
{
    const char* fileName = "driverUsers.txt";
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

void Driver::logout()
{
    std::cout << "Logout successful!" << std::endl;
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

            delete driver;
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
     messages->printAllMessages();
}

void Driver::acceptOrder(const Order& order) 
{
    Order* foundOrder = orders->findOrderById(order.getId());
    if (foundOrder) 
    {
        foundOrder->setStatus(Status::Accepted);
    }
}

void Driver::declineOrder(int id)
{
    Order* foundOrder = orders->findOrderById(id);
    if (foundOrder)
    {
        foundOrder->setStatus(Status::Canceled);
    }
}

void Driver::finishOrder(int id)
{
    Order* foundOrder = orders->findOrderById(id);
    if (foundOrder)
    {
        foundOrder->setStatus(Status::Completed);
    }
}

void Driver::acceptPayment(int id, double amount) 
{
    Order* foundOrder = orders->findOrderById(id);
    if (foundOrder) 
    {
        foundOrder->setPaymentAmount(amount);
        foundOrder->setPaymentStatus(PaymentStatus::Paid);
    }
}

void Driver::addRating(const Rating& rating)
{
    ratings.pushBack(rating);
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