#pragma once
#include "Vector.hpp"
#include "Message.h"

class MessageManager
{
    Vector<Message> messages;

public:
    void addMessage(const Message& message);
    void printUnreadMessages() const;
    void removeMessage(unsigned int messageId);
    void deleteAllMessages();
    void printAllMessages() const;
    Message* getMessageById(unsigned int messageId);
};