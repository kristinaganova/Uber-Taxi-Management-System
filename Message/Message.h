#pragma once
#include "MyString.h"

class Message
{
    MyString content;
    mutable bool read = false;
    unsigned int id;

public:
    Message(const MyString& content, unsigned int id);
    Message();

    const MyString& getContent() const;
    unsigned int getId() const;
    bool isRead() const;
    void markAsRead() const ;
};
