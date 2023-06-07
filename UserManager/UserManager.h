#pragma once
#include "User.h"
#include "Vector.hpp"

class UserManager
{
	Vector<User*> users;

	void free();
	void copyFrom(const UserManager& other);
	void moveFrom(UserManager&& other);
public:
	void addUser(User* newUser);
	~UserManager();
	UserManager();

	UserManager(const UserManager& other);
	UserManager& operator=(const UserManager& other);

	UserManager(UserManager&& other) noexcept;
	UserManager& operator=(UserManager&& other) noexcept;

	UserType getTypeByIndex(unsigned int index) const;
	User* findUserByUserName(const MyString& userName);
	//void rateDriver(const MyString& driverName, const Rating& rating);

	void saveAllRegisteredUserToFile(const char* fileName) const;
	void loadAllUsersFromFile();
};

