#include "User.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <cstring>
#include "helpers.h"
#include "MessageManager.h"

User::User(UserType type, const MyString& firstName, const MyString& lastName, const MyString& username, const MyString& password)
     : type(type)
{
    setName(firstName);
    setLastName(lastName);
    setUsername(username);
    setPassword(password);
    initializeMessageStore();
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

UniquePointer<MessageStore>& User::getMessages()
{
    return messages;
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

void User::initializeMessageStore()
{
    messages = UniquePointer<MessageStore>(new MessageStore());
}

void User::sendMessage(const SharedPtr<User>& receiver, const MyString& content)
{
    MessageManager::getInstance().sendMessage(this, receiver, content);
}

void User::logout()
{
    std::cout << "Logged out successfully!" << std::endl;
}

bool User::login(const MyString& username, const MyString& password)
{
    if (this->username == username && this->password == password)
    {
        return true;
    }
    std:: cout << "Error: Not correct username or password!" << std::endl;
    return false;
}
