#pragma once
#include "Vector.hpp"
#include "MyString.h"

enum class UserType { CLIENT, DRIVER };

class User
{
protected:
	UserType type;
	MyString firstName;
	MyString lastName;
	MyString username;
	MyString password;

public:
	User() = default;
	User(UserType type, const MyString& firstName, const MyString& lastName, 
		                const MyString& username, const MyString& password);
	virtual ~User() = default;

	const UserType& getUserType() const;
	const MyString& getFirstName() const;
	const MyString& getLastName() const;
	const MyString& getUsername() const;
	const MyString& getPassword() const;

	void setType(const UserType& type);
	void setName(const MyString& name);
	void setLastName(const MyString& name);
	void setUsername(const MyString& username);
	void setPassword(const MyString& password);

	virtual void saveRegisteredUserToFile(const User& user, const char* fileName) = 0;
	virtual Vector<User*> loadRegisteredUserFromFile(const char* fileName) = 0;

	virtual void registerUser() = 0;
	virtual bool login() = 0;
	virtual void logout() = 0;
};