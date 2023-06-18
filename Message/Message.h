#pragma once
#include "MyString.h"
#include "User.h"
#include "SharedPtr.hpp"

class User;

class Message
{
    static int nextId;
    MyString content;
    SharedPtr<User> sender;
    SharedPtr<User> receiver;
    mutable bool read = false;
    unsigned int id;

public:
    Message(const MyString& content, unsigned int id);
    Message(const MyString& content, const SharedPtr<User>& sender, const SharedPtr<User>& receiver, unsigned int id);
    Message();

    void setReceiver(SharedPtr<User> receiver);

    const MyString& getContent() const;
    const SharedPtr<User>& getSender() const;
    const SharedPtr<User>& getReceiver() const;
    unsigned int getId() const;
    bool isRead() const;
    void markAsRead() const ;
};