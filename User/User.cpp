#include "User.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <cstring>
#include "helpers.h"

User::User(UserType type, const MyString& firstName, const MyString& lastName, const MyString& username, const MyString& password)
     : type(type)
{
    setName(firstName);
    setLastName(lastName);
    setUsername(username);
    setPassword(password);
}

const UserType& User::getUserType() const
{
    return type;
}

const MyString& User::getFirstName() const
{
	return firstName;
}

const MyString& User::getLastName() const
{
	return lastName;
}

const MyString& User::getUsername() const
{
	return username;
}

const MyString& User::getPassword() const
{
    return password;
}

void User::setType(const UserType& type)
{
    this->type = type;
}

void User::setName(const MyString& name)
{
    if (!isValidName(name))
    {
        return;
    }
    this->firstName = name;
}

void User::setLastName(const MyString& name)
{
    if (!isValidName(name))
    {
        return;
    }
    this->lastName = name;
}

void User::setUsername(const MyString& username)
{
    if (!isValidUsername(username))
    {
        return;
    }
    this->username = username;
}

void User::setPassword(const MyString& password)
{
    if (!isValidPassword(password))
    {
        return;
    }
    this->password = password;
}

void User::saveRegisteredUserToFile(const User& user, const char* fileName)
{
    std::ofstream file(fileName, std::ios::app);
    if (!file.is_open())
    {
        std::cout << "Error: Unable to open file " << fileName << " for writing." << std::endl;
        return;
    }
    file << (char*)(user.type) << ", "
        << user.firstName << ", "
        << user.lastName << ", "
        << user.username << ", "
        << user.password << std::endl;

    file.close();
}