#include "MessageManager.h"

unsigned int MessageManager::nextId = 1;

MessageManager::MessageManager() = default;

MessageManager& MessageManager::getInstance()
{
    static MessageManager instance;
    return instance;
}

void MessageManager::addMessage(const Message& message)
{
    messages.pushBack(message);
}

void MessageManager::printUnreadMessages() const
{
    for (size_t i = 0; i < messages.getSize(); i++)
    {
        if (!messages[i].isRead())
        {
            std::cout << messages[i].getContent() << std::endl;
            messages[i].markAsRead();
        }
    }
}

void MessageManager::removeMessage(unsigned int messageId)
{
    for (size_t i = 0; i < messages.getSize(); i++)
    {
        if (messages[i].getId() == messageId)
        {
            messages.popAt(i);
            break;
        }
    }
}

void MessageManager::deleteAllMessages()
{
    messages.clear();
}

void MessageManager::printAllMessages() const
{

    for (size_t i = 0; i < messages.getSize(); i++)
    {
        std::cout << "Message " << messages[i].getId() << std::endl;
        std::cout << messages[i].getContent() << std::endl;
        messages[i].markAsRead();
    }
}

Message* MessageManager::getMessageById(unsigned int messageId)
{
    for (size_t i = 0; i < messages.getSize(); i++)
    {
        if (messages[i].getId() == messageId)
        {
            return &messages[i];
        }
    }
    return nullptr;
}

unsigned int MessageManager::getNextId() const
{
    return nextId++;
}
