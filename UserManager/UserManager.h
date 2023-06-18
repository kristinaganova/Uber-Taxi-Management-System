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

public:
    static UserManager& getInstance();
    void addUser(User* newUser);
    ~UserManager() = default;

    const Vector<User*> getUsers() const;
    size_t getUsersCount() const;
    void rateDriver(const MyString& driverName, const Rating& rating);
    Vector<Driver*> getDrivers() const;
    UserType getTypeByIndex(unsigned int index) const;
    User* findUserByName(const MyString& name);
    User* findUserByUserName(const MyString& userName);

    void clearAndSaveAllRegisteredClientsToFile(const char* fileName) const;

    void saveAllRegisteredUserToFile(const char* fileName) const;
    void loadAllUsersFromFile();
};