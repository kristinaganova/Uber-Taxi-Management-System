#pragma once
#include "Message.h"
#include "Vector.hpp"

class Message;

class MessageStore 
{
    static unsigned int nextId;
    Vector<Message> messages;

public:
    void addMessage(const Message& message);
    void printUnreadMessages() const;
    void removeMessage(unsigned int messageId) ;
    void deleteAllMessages();
    void printAllMessages() const;

    unsigned int getNextId();
    Message* getMessageById(unsigned int messageId);
};