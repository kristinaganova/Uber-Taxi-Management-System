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

void UserManager::copyFrom(const UserManager& other)
{
    for (size_t i = 0; i < other.users.getSize(); i++)
    {
        users.pushBack(other.users[i]->clone());
    }
}

void UserManager::moveFrom(UserManager&& other)
{
    users = other.users;
    other.users = Vector<User*>();
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

UserManager::UserManager(const UserManager& other)
{
    copyFrom(other);
}

UserManager& UserManager::operator=(const UserManager& other)
{
    if (this != &other)
    {
        free();
        copyFrom(other);
    }
    return *this;
}

UserManager::UserManager(UserManager&& other) noexcept
{
    moveFrom(std::move(other));
}

UserManager& UserManager::operator=(UserManager&& other) noexcept
{
    if (this != &other)
    {
        free();
        moveFrom(std::move(other));
    }
    return *this;
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


//void UserManager::rateDriver(const MyString& driverName, const Rating& rating)
//{
//    Driver* driver = (Driver*)findUserByName(driverName);
//    driver->addRating(rating);
//}

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

