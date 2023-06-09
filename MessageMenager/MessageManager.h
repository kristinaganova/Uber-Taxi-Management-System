#pragma once

#include "Vector.hpp"
#include "Message.h"

class MessageManager
{
    Vector<Message> messages;
    static unsigned int nextId;

    MessageManager();

    MessageManager(const MessageManager& other) = delete;
    MessageManager& operator=(const MessageManager& other) = delete;

    MessageManager(MessageManager&& other) noexcept = delete;
    MessageManager& operator=(MessageManager&& other) noexcept = delete;

public:
    static MessageManager& getInstance();

    void addMessage(const Message& message);
    void printUnreadMessages() const;
    void removeMessage(unsigned int messageId);
    void deleteAllMessages();
    void printAllMessages() const;
    Message* getMessageById(unsigned int messageId);
    unsigned int getNextId() const;
};
