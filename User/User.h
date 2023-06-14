#pragma once
#include "Vector.hpp"
#include "MyString.h"
#include "MessageStore.h"
#include "UniquePtr.hpp"
#include "SharedPtr.hpp"

class MessageStore;

enum class UserType { CLIENT, DRIVER };

class User
{
protected:
	UserType type;
	MyString firstName;
	MyString lastName;
	MyString username;
	MyString password;
	UniquePointer<MessageStore> messages;
public:
	User() = default;
	User(UserType type, const MyString& firstName, const MyString& lastName, 
		 const MyString& username, const MyString& password);

	virtual ~User() = default;
	virtual User* clone() const = 0;

	const UserType& getUserType() const;
	const MyString& getFirstName() const;
	const MyString& getLastName() const;
	const MyString& getUsername() const;
	UniquePointer<MessageStore>& getMessages();

	void setType(const UserType& type);
	void setName(const MyString& name);
	void setLastName(const MyString& name);
	void setUsername(const MyString& username);
	void setPassword(const MyString& password);
	void initializeMessageStore();

	virtual void saveRegisteredUserToFile(const User& user, const char* fileName) = 0;
	virtual Vector<User*> loadRegisteredUserFromFile(const char* fileName) = 0;
	void sendMessage(const SharedPtr<User>& receiver, const MyString& content);

	virtual void registerUser() = 0;
	void logout();
	bool login(const MyString& username, const MyString& password);
};