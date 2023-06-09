#include "UserManager.h"
#include "Client.h"
#include "Driver.h"
#include "Rating.h"

void UserManager::free()
{
    for (size_t i = 0; i < users.getSize(); i++)
    {
        delete users[i];
    }
}

UserManager& UserManager::getInstance()
{
    static UserManager instance;
    return instance;
}

void UserManager::addUser(User* newUser)
{
	users.pushBack(newUser);
}

UserManager::~UserManager()
{
    free();
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

void UserManager::loadAllUsersFromFile()
{
    users.clear();

    // Load client users
    Client client;
    Vector<User*> clientRegisteredUsers = client.loadRegisteredUserFromFile("ClientUsers.txt");
    for (size_t i = 0; i < clientRegisteredUsers.getSize(); i++)
    {
        User* user = clientRegisteredUsers[i]->clone();
        users.pushBack(user);
        delete clientRegisteredUsers[i]; 
    }
    clientRegisteredUsers.clear(); 

    // Load driver users
    Driver driver;
    Vector<User*> driverRegisteredUsers = driver.loadRegisteredUserFromFile("driverUsers.txt");
    for (size_t i = 0; i < driverRegisteredUsers.getSize(); i++)
    {
        User* user = driverRegisteredUsers[i]->clone();
        users.pushBack(user);
        delete driverRegisteredUsers[i]; 
    }
    driverRegisteredUsers.clear(); 
}
