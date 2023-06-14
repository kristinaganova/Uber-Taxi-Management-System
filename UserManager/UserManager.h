#pragma once

#include "User.h"
#include "Vector.hpp"

class Driver;
class Rating;

class UserManager
{
    Vector<User*> users;

    UserManager();

    UserManager(const UserManager& other) = delete;
    UserManager& operator=(const UserManager& other) = delete;

    UserManager(UserManager&& other) noexcept = delete;
    UserManager& operator=(UserManager&& other) noexcept = delete;

    void free();
public:
    static UserManager& getInstance();
    void addUser(User* newUser);
    ~UserManager();

    void rateDriver(const MyString& driverName, const Rating& rating);
    Vector<Driver*> getDrivers() const;
    UserType getTypeByIndex(unsigned int index) const;
    User* findUserByName(const MyString& name);
    User* findUserByUserName(const MyString& userName);

    void saveAllRegisteredUserToFile(const char* fileName) const;
    void loadAllUsersFromFile();
};