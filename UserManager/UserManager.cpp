#include "UserManager.h"
#include "Client.h"
#include "Driver.h"
#include "Rating.h"

UserManager& UserManager::getInstance()
{
    static UserManager instance;
    return instance;
}

void UserManager::addUser(User* newUser)
{
	users.pushBack(newUser);
}

UserManager::UserManager() : users(Vector<User*>()) {}

Vector<Driver*> UserManager ::getDrivers() const
{
    Vector<Driver*> drivers; 

    for (size_t i = 0; i < users.getSize(); i++)
    {
        if (users[i]->getUserType() == UserType::DRIVER)
        {
            drivers.pushBack(static_cast<Driver*>(users[i]));
        }
    }

    return drivers;
}

UserType UserManager::getTypeByIndex(unsigned int index) const
{
	if (index > users.getSize())
		throw std::out_of_range("Invalid index");

	return users[index]->getUserType();
}

User* UserManager::findUserByUserName(const MyString& userName)
{
    for (size_t i = 0; i < users.getSize(); i++)
    {
        if (users[i] && users[i]->getUsername() == userName)
            return users[i];
    }
    return nullptr;
}

User* UserManager::findUserByName(const MyString& name)
{
    for (size_t i = 0; i < users.getSize(); i++)
    {
        if (users[i] && users[i]->getFirstName() == name)
            return users[i];
    }
    return nullptr;
}

const Vector<User*> UserManager::getUsers() const
{
    return users;
}

size_t UserManager::getUsersCount() const
{
    return (getUsers().getSize());
}

void UserManager::rateDriver(const MyString& driverName, const Rating& rating)
{
    Driver* driver = static_cast<Driver*>(UserManager::findUserByUserName(driverName));
    driver->addRating(rating);
}

void UserManager::saveAllRegisteredUserToFile(const char* fileName) const
{
	for (size_t i = 0; i < users.getSize(); i++)
	{
		users[i]->saveRegisteredUserToFile(*users[i], fileName);
	}
}

void UserManager::clearAndSaveAllRegisteredClientsToFile(const char* fileName) const
{
    std::ofstream file(fileName);
    if (!file)
    {
        throw std::runtime_error("Failed to open the file.");
    }

    file.close();

    file.open(fileName, std::ios::app);
    if (!file)
    {
        throw std::runtime_error("Failed to open the file for writing.");
    }

    for (size_t i = 0; i < users.getSize(); i++)
    {
        if (users[i]->getUserType() == UserType::CLIENT)
        {
            Client* client = static_cast<Client*>(users[i]);
            client->saveRegisteredUserToFile(*client, fileName);
        }
    }

    file.close();
}

void UserManager::loadAllUsersFromFile()
{
    users.clear();

    Client client;
    Vector<User*> clientRegisteredUsers = client.loadRegisteredUserFromFile("ClientUsers.txt");
    for (size_t i = 0; i < clientRegisteredUsers.getSize(); i++)
    {
        User* user = clientRegisteredUsers[i]->clone();
        users.pushBack(user);
        delete clientRegisteredUsers[i]; 
    }
    clientRegisteredUsers.clear(); 

    Driver driver;
    Vector<User*> driverRegisteredUsers = driver.loadRegisteredUserFromFile("driverUsers.txt");
    for (size_t i = 0; i < driverRegisteredUsers.getSize(); i++)
    {
        User* user = driverRegisteredUsers[i]->clone();
        users.pushBack(user); 
    }
    driverRegisteredUsers.clear(); 
}